#include <math.h>
#include "shot_detector.hpp"

#define FPS 24

static bool is_shot_valid (const shot &shotv)
{
    if (shotv.start >= 0 && shotv.end >= 0)
        return true;
    return false;
}

static bool good_shot (const shot &shotv, const frame_info &fi, 
                        const int min_len)
{
    if (shotv.end - shotv.start >= min_len)
        return true;
    return false;
}

static void shot_merge (shot &into, const shot &m)
{
#ifdef DEBUG
    std::cout << "merge " << m.start << "," << m.end << " to "
        << into.start << "," << into.end << "," << into.start_frame_type << std::endl;
#endif
    into.end = m.end;
    into.end_frame_type = m.end_frame_type;
    into.avg_sum += m.avg_sum;
    into.var_sum += m.var_sum;
    into.num += m.num;
    into.end_cut = m.end_cut;
    into.append_boundaries (m.boundaries);
}
/*
static float cmp_shot (const shot &shotv1, const shot &shotv2)
{
    return fabs((float)shotv1.avg_sum / shotv1.num 
               - (float)shotv2.avg_sum / shotv2.num);
}
*/
shot::shot (unsigned int istart, unsigned int iend, unsigned int  iavg_sum, 
            unsigned int ivar_sum, unsigned int inum, frametype istarttype, 
            frametype iendtype, unsigned int iendcut)
{
    start = istart;
    end = iend;
    avg_sum = iavg_sum;
    var_sum = ivar_sum;
    num = inum;
    start_frame_type = istarttype;
    end_frame_type = iendtype;
    end_cut = iendcut;
    boundaries.clear ();
}

std::ostream& operator << (std::ostream &os, const shot &s)
{
    os << "start:" << s.start << ','
       << "end:" << s.end << ','
       << "avg_sum:" << s.avg_sum << ','
       << "var_sum:" << s.var_sum << ','
       << "num:" << s.num << ','
       << "start_frame_type:" << s.start_frame_type << ','
       << "end_frame_type:" << s.end_frame_type << std::endl;
    return os;
}

shot & shot::operator = (const shot &other)
{
    if (this == &other)
        return *this;
    start = other.start;
    end = other.end;
    avg_sum = other.avg_sum;
    var_sum = other.var_sum;
    num = other.num;
    start_frame_type = other.start_frame_type;
    end_frame_type = other.end_frame_type;
    end_cut = other.end_cut;
    boundaries.clear ();
    boundaries = other.boundaries;
    /*for (std::vector<frame_info>::const_iterator it = other.boundaries.begin ();
            it != other.boundaries.end (); ++it ) {
        boundaries.push_back (*it);    
    }*/
    return *this;
}
void shot::set_boundaries (const std::vector<frame_info> in_boundaries)
{
    boundaries.clear ();
    boundaries = in_boundaries;
}

void shot::append_boundaries (const std::vector<frame_info> in_boundaries)
{
    boundaries.reserve (boundaries.size () + in_boundaries.size ());
    boundaries.insert (boundaries.end(), in_boundaries.begin (), in_boundaries.end ());
}


shot_detector::shot_detector (const unsigned int width, const unsigned int height, 
                const unsigned int block_w, const unsigned int block_h,
                const config &iconfig)
                    :_sbd (width, height, 
                           block_w, block_h, iconfig.hist_th, 
                           iconfig.diff_cnt_th, iconfig.var_th),
                    _status (NO_SHOT),
                    _prev_shot (-1, -1, 0, 0, 0, BOUNDARY, BOUNDARY, -1),
                    _prev_boundary_ts (-1),
                    _prev_boundary_type (BOUNDARY),
                    _black_skipping (false),
                    _black_start (-1),
                    _curr_ts (-1),
                    _prev_ts (-1),
                    _prev_prev_ts (-1),
                    _shot_avg (0),
                    _shot_var (0),
                    _shot_num (0),
                    _stared (true),
                    _min_len (iconfig.min_len)
{
}

shot_detector::~shot_detector ()
{
}

void shot_detector::print_status ()
{
    std::cout << "status:" << _status << std::endl
         << "_prev_shot:\n" << _prev_shot
         << "_prev_boundary_ts:" << _prev_boundary_ts << std::endl
         << "_prev_boundary_type:" << _prev_boundary_type << std::endl
         << "_curr_ts:" << _curr_ts << std::endl;
}

void shot_detector::restart (const unsigned char *first_frame, unsigned int first_ts)
{
    _sbd.start (first_frame, first_ts);
    _status = NO_SHOT;
    _prev_shot = shot (-1, -1, 0, 0, 0, BOUNDARY, BOUNDARY, -1);
    _prev_boundary_type = BOUNDARY;
    _prev_boundary_ts = first_ts;
    _black_skipping = false;
    _black_start =  -1;
    _curr_ts = -1;
    _prev_ts = -1;
    _prev_prev_ts = -1;
    _shot_avg = 0;
    _shot_var = 0;
    _shot_num = 0;
    _stared = true;
    _boundaries_cache.clear ();
}

shot shot_detector::flush ()
{
    shot ret_shot (-1, -1, 0, 0, 0, BOUNDARY, BOUNDARY, -1);
    shot new_shot (_prev_boundary_ts, _prev_ts, 0, 0, 0, BOUNDARY, BOUNDARY, -1);
    if (is_shot_valid (_prev_shot)) {
        ret_shot = _prev_shot;
        _prev_shot = new_shot;
    }
    return ret_shot;
}

shot shot_detector::detect (const unsigned char *curr_frame, const unsigned int curr_ts)
{
#ifdef DEBUG
    std::cout << "=== begin detect" << std::endl;
    print_status ();
#endif
    _curr_ts = curr_ts;
    shot ret_shot (-1, -1, 0, 0, 0, BOUNDARY, BOUNDARY, -1);
    frame_info ret;
    ret = _sbd.detect (curr_frame, curr_ts);
    _shot_avg += ret.avg;
    _shot_var += ret.var;
    _shot_num++;
    if (ret.frame_type != BLACK) {
        if (ret.frame_type == BOUNDARY || _black_skipping) {

            if (_black_skipping && _black_start == (unsigned int)_prev_shot.end) {
                //last boundary before black start found, do not need create new shot
                _prev_shot.end_frame_type = BLACK;
                _prev_shot.end_cut = -1;
                _prev_boundary_ts = ret.prev_ts;
                _black_skipping = false;
                _black_start = -1;
                _prev_boundary_type = BLACK;
            } else {
                shot new_shot (_prev_boundary_ts, ret.prev_ts, _shot_avg, 
                               _shot_var, _shot_num, _prev_boundary_type, 
                               BOUNDARY, ret.cut);
                _shot_avg = 0;
                _shot_var = 0;
                _shot_num = 0;
                if (_black_skipping) {
                    new_shot.end = _black_start;
                    new_shot.end_frame_type = BLACK;
                    new_shot.end_cut = -1;
                    _black_skipping = false;
                    _black_start = -1;
                }
                if (!_boundaries_cache.empty () 
                     && fabs(_boundaries_cache.back().prev_ts - new_shot.end)
                        < 1000.0 / FPS) {
                    _boundaries_cache.pop_back ();
                }
                new_shot.set_boundaries (_boundaries_cache);
                if (good_shot (new_shot, ret, _min_len) || new_shot.end_frame_type == BLACK) {
                    ret_shot = _prev_shot;
                    _prev_shot = new_shot;
                    if (new_shot.end_frame_type == BLACK) {
                        _prev_boundary_ts = ret.prev_ts;
                        _prev_boundary_type = BLACK;
                    }
                    else {
                        _prev_boundary_ts = curr_ts;
                        _prev_boundary_type = BOUNDARY;

                    }
                    _prev_prev_ts = _prev_ts;
                    _prev_ts = curr_ts;
                    _boundaries_cache.clear ();
                    return ret_shot;
                } else {
                    if (is_shot_valid (_prev_shot) 
                            && new_shot.end_cut > _prev_shot.end_cut) {
                        shot_merge (_prev_shot, new_shot);
                        _prev_boundary_ts = curr_ts;
                    } else {
                         _boundaries_cache.push_back (ret);
                    }
                }
            }
        }
    } else {
        //got black frame
        if (_black_skipping == false) {//start skipping black frames
            _black_start = _prev_prev_ts;//ret.prev_ts;
            _black_skipping = true;
        }
    }
    
#ifdef DEBUG
    std::cout << "=== end detect" << std::endl;
    print_status ();
#endif
    _prev_prev_ts = _prev_ts;
    _prev_ts = curr_ts;
    return ret_shot;
}

void shot_detector::reset_config (const config &iconfig)
{
    _sbd.reset_config (iconfig.hist_th, iconfig.diff_cnt_th, iconfig.var_th);
}
        
