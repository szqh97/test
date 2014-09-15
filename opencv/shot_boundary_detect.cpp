#include <stdexcept>
#include <string.h>
#include <stdlib.h>
#include"shot_boundary_detect.hpp"

#ifdef DEBUG
  #include <iostream>
  #include <stdio.h>
  using namespace std;
#elif defined DEBUGL
  #include <iostream>
  #include <stdio.h>
  using namespace std;
#endif

static void calc_hist (const unsigned char *frame_buffer, const unsigned int width, 
                    const unsigned int height, const unsigned int block_w, 
                    const unsigned int block_h, unsigned int **hist)
{
    if (frame_buffer == NULL)
        throw std::runtime_error ("input buffer is NULL");
    if (block_w < 1 || block_h < 1)
        throw std::runtime_error ("input block count is incorrect");
    unsigned int row_step = width / block_w;
    unsigned int col_step = height / block_h;
    for (unsigned int i = 0; i < block_w * block_h; ++i)
        memset (hist[i], 0, 256 * sizeof (unsigned int));
    for(unsigned int i = 0; i < height; ++i) {
        unsigned int y = i / col_step;
        y = y < block_h ? y : block_h - 1;
        for (unsigned int j = 0; j < width; ++j) {
            unsigned int x = j / row_step;
            x = x < block_w ? x : block_w - 1;
            ++(hist[y * block_w + x][(int)frame_buffer[width * i + j]]);
        }
    }
}

#ifdef DEBUG
static void print_hist (unsigned int **hist, int total)
{
    return;
    cerr << "hist:" << endl;
    for (int i = 0; i < total; ++i) {
        for (int j = 0; j < 256; ++j)
            cerr << hist[i][j] << " ";
        cerr << endl;
    }
}
#endif

//only black regard as boundary
static bool check_frame_black (const unsigned char *frame_buffer, const unsigned int width, 
            const unsigned int height, float th_var, float th_avg, float &var, float &gray_avg)
{
    if (frame_buffer == NULL)
        throw std::runtime_error ("input buffer is NULL");
    gray_avg = 0.0;
    for(unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            gray_avg += (int)frame_buffer[width * i + j];
        }
    }
    gray_avg = gray_avg / (height * width);
    var = 0.0;
    for(unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            var += ((int)frame_buffer[width * i + j] - gray_avg) 
                * ((int)frame_buffer[width * i + j] - gray_avg);
        }
    }
    var = var / (height * width);
#ifdef DEBUG
    cerr << "var:" << var << " avg:" << gray_avg << endl;
#endif
    if (var < th_var && gray_avg < th_avg)
        return true;

    return false;
}

static frametype check_hist_diff (unsigned int **hist1, unsigned int **hist2,
            const unsigned int block_w, const unsigned int block_h,
            float hist_th, unsigned int diff_cnt_th, unsigned int *hist_num, 
            unsigned int &diff_cnt)
{
    if (hist1 == NULL || hist2 == NULL)
        throw std::runtime_error ("hist is NULL");
    unsigned int total_block = block_w * block_h;
    
    diff_cnt = 0;
    for (unsigned int i = 0; i < total_block; ++i) {
        float hist_diff = 0;
        for (unsigned int j = 0; j < 256; ++j)
            hist_diff += abs (hist1[i][j] - hist2[i][j]);
        hist_diff = hist_diff / (2.0 * hist_num[i]);
#ifdef DEBUG
        cerr << "hist diff:" << hist_diff << endl;
#endif
        if (hist_diff > hist_th)
            diff_cnt++;
    }
#ifdef DEBUG
    cerr << "diff count:" << diff_cnt << endl;
#endif
    if (diff_cnt >= diff_cnt_th)
        return BOUNDARY;
    
    return NORMAL;
}

shot_boundary_detector::shot_boundary_detector (const unsigned int width, 
        const unsigned int height,
        const unsigned int block_w, const unsigned int block_h,
        const float hist_th, const int diff_cnt_th, const float var_th,
        const float avg_th)
{
    _width = width;
    _height = height; 
    _block_w = block_w;
    _block_h = block_h;
    _hist_th = hist_th;
    _diff_cnt_th = diff_cnt_th;
    _var_th = var_th;
    _avg_th = avg_th;
    _hist_num = NULL;
    _curr_frame_hist = NULL;
    _prev_frame_hist = NULL;
    _started = false;
    _prev_black = false;

}

shot_boundary_detector::shot_boundary_detector (const shot_boundary_detector &other)
{
    _width = other._width;
    _height = other._height; 
    _block_w = other._block_w;
    _block_h = other._block_h;
    _hist_th = other._hist_th;
    _diff_cnt_th = other._diff_cnt_th;
    _var_th = other._var_th;
    _hist_num = other._hist_num;
    _curr_frame_hist = other._curr_frame_hist;
    _prev_frame_hist = other._prev_frame_hist;
    _started = other._started;
    _prev_black = other._prev_black;
}

shot_boundary_detector &shot_boundary_detector::operator = (const shot_boundary_detector &other)
{
    if (this == &other)
        return *this;
    _width = other._width;
    _height = other._height; 
    _block_w = other._block_w;
    _block_h = other._block_h;
    _hist_th = other._hist_th;
    _diff_cnt_th = other._diff_cnt_th;
    _var_th = other._var_th;
    _hist_num = other._hist_num;
    _curr_frame_hist = other._curr_frame_hist;
    _prev_frame_hist = other._prev_frame_hist;
    _started = other._started;
    _prev_black = other._prev_black;
    
    return *this;
}

shot_boundary_detector::~shot_boundary_detector ()
{
    if (_prev_frame_hist) {
        for (unsigned int i = 0; i < _block_h; ++i)//rows
            for (unsigned int j = 0; j < _block_w; ++j) { //cols
                if (_prev_frame_hist[i * _block_w + j] != NULL)
                    delete []_prev_frame_hist[i * _block_w + j];
            }
        delete []_prev_frame_hist;
    }
    if (_curr_frame_hist) {
        for (unsigned int i = 0; i < _block_h; ++i)//rows
            for (unsigned int j = 0; j < _block_w; ++j) { //cols
                if (_curr_frame_hist[i * _block_w + j] != NULL)
                    delete []_curr_frame_hist[i * _block_w + j];
            }
        delete []_curr_frame_hist;
    }
    if (_hist_num)
        delete []_hist_num;
}

void shot_boundary_detector::start (const unsigned char *first_frame_buffer,
                                    const unsigned int first_ts)
{
    if (first_frame_buffer == NULL)
        throw std::runtime_error ("input buffer is NULL");
    if (check_params () == false)
        throw std::runtime_error ("input params is wrong");
    if (_started || _prev_frame_hist != NULL || _curr_frame_hist != NULL)
        throw std::runtime_error ("already start");
    _prev_frame_hist = new unsigned int*[_block_h * _block_w];
    _curr_frame_hist = new unsigned int*[_block_h * _block_w];
    //row first store
    for (unsigned int i = 0; i < _block_h; ++i)//rows
        for (unsigned int j = 0; j < _block_w; ++j) { //cols
            _prev_frame_hist[i * _block_w + j] = new unsigned int[256];
            _curr_frame_hist[i * _block_w + j] = new unsigned int[256];
    }
    
    _hist_num = new unsigned int[_block_h * _block_w];
    memset (_hist_num, 0, _block_h * _block_w * sizeof (unsigned int));
    unsigned int row_step = _width / _block_w;
    unsigned int col_step = _height / _block_h;
    for(unsigned int i = 0; i < _height; ++i) {
        unsigned int y = i / col_step;
        y = y < _block_h ? y : _block_h - 1;
        for (unsigned int j = 0; j < _width; ++j) {
            unsigned int x = j / row_step;
            x = x < _block_w ? x : _block_w - 1;
            _hist_num[y * _block_w + x]++;
        }
    }
    
    _prev_black = check_frame_black (first_frame_buffer, _width,
                                    _height, _var_th, _avg_th, _prev_var, 
                                    _prev_avg);
    if (_prev_black == false)
        calc_hist (first_frame_buffer, _width, _height, _block_w, _block_h,
                    _prev_frame_hist);
    _started = true;
    _prev_ts = first_ts;
    _prev_cut = -1;
}

//detect if prev frame is a shot boundary
frame_info shot_boundary_detector::detect (const unsigned char *current_frame_buffer,
                                    const unsigned int curr_ts)
{
#ifdef DEBUGL
  cerr << "bdetect " << _prev_ts << " " << curr_ts;
#endif
    if (current_frame_buffer == NULL)
        throw std::runtime_error ("input buffer is NULL");

    if (!_started)
        throw std::runtime_error ("detection not start");

    frame_info fi;
    if (_prev_black) {
        fi.var = _prev_var;
        fi.avg = _prev_avg;
        fi.frame_type = BLACK;
        fi.prev_ts = _prev_ts;
        fi.cut = _prev_cut;
        _prev_black = check_frame_black (current_frame_buffer, _width,
                                         _height, _var_th, _avg_th, _prev_var,
                                         _prev_avg);
        calc_hist (current_frame_buffer, _width, _height, _block_w, _block_h,
                     _prev_frame_hist);
        _prev_ts = curr_ts;
#ifdef DEBUGL
        cerr << ":" << fi.var << " " << fi.avg << " " <<  fi.cut << " " 
            << fi.frame_type << endl;
#endif
        return fi;
    }
    calc_hist (current_frame_buffer, _width, _height, _block_w, _block_h,
                _curr_frame_hist);
#ifdef DEBUG
    print_hist (_prev_frame_hist, _block_w * _block_h);
    print_hist (_curr_frame_hist, _block_w * _block_h);
#endif
    fi.frame_type = check_hist_diff (_prev_frame_hist, _curr_frame_hist, _block_w, 
                                _block_h, _hist_th, _diff_cnt_th, _hist_num, fi.cut);
    fi.var = _prev_var;
    fi.avg = _prev_avg;
    fi.prev_ts = _prev_ts;
    _prev_black = check_frame_black (current_frame_buffer, _width,
                                     _height, _var_th, _avg_th, _prev_var, 
                                     _prev_avg);

    unsigned int **t_hist_p = _prev_frame_hist;
    //switch frame hist pointer
    _prev_frame_hist = _curr_frame_hist;
    _curr_frame_hist = t_hist_p;
    _prev_ts = curr_ts;
    _prev_cut = fi.cut;
#ifdef DEBUGL
        cerr << ":" << fi.var << " " << fi.avg << " " <<  fi.cut << " " 
            << fi.frame_type << endl;
#endif
    return fi;
}

void shot_boundary_detector::reset_config (const float hist_th, 
                    const int diff_cnt_th, const float var_th)
{
    _hist_th = hist_th;
    _diff_cnt_th = diff_cnt_th;
    _var_th = var_th;
    if (check_params () == false)
        throw std::runtime_error ("input params is wrong");
}

bool shot_boundary_detector::check_params () const
{
#ifdef DEBUG
    cerr << _width << "," << _height << ","
         << _block_w << "," << _block_h << endl;
#endif
    if (_width < 4 || _height < 4 || _block_w <= 0 || _block_h <= 0)
        return false;
    else
        return true;
}

void shot_boundary_detector::print_config () const
{
#ifdef DEBUGL
    cerr << "width:" << _width << endl
        << "height:" << _height << endl
        << "block_w:" << _block_w << endl
        << "block_h:" << _block_h << endl
        << "hist_th:" << _hist_th << endl
        << "diff_cnt_th:" << _diff_cnt_th << endl
        << "var_th:" << _var_th << endl
        << "avg_th:" << _avg_th << endl;
#endif
}
