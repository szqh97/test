#ifndef _SHOT_DETECTOR_H_
#define _SHOT_DETECTOR_H_

#include "shot_boundary_detect.hpp"
#include <vector>
#include <iostream>

enum status {NO_SHOT, NEW_SHOT, PENDING};

struct config
{
    float hist_th; //control judgging shot boundary, default is 0.5
    int diff_cnt_th; //control judgging shot boundary, default is 5
    float var_th; //control judge black frame, default is 100.0
    int min_len; //control minimum length of one shot with 
                  //no black frame at beign and end 
};

struct shot
{
    shot (unsigned int istart, unsigned int iend, unsigned int  iavg_sum, 
          unsigned int ivar_sum, unsigned int inum, frametype istarttype,
          frametype iendtype, unsigned int iendcut);
    shot & operator = (const shot &other);
    friend std::ostream& operator << (std::ostream &os, const shot &s);
    
    void set_boundaries (const std::vector<frame_info> in_boundaries);
    void append_boundaries (const std::vector<frame_info> in_boundaries);

    int start; //shot start timestamp
    int end; //shot end timestamp
    int avg_sum; //average gray sumary of the shot
    int var_sum; //boundary variance of the shot
    int num; //total boundaries count
    frametype start_frame_type; //start frame type: normal-boundary/black-frame
    frametype end_frame_type;//end frame type: normal-boundary/black-frame
    unsigned int end_cut; //end boundary intensity
    std::vector<frame_info> boundaries; //middle boundaries timestamp
};

class shot_detector
{
    public:
        shot_detector (const unsigned int width, const unsigned int height, 
                const unsigned int block_w, const unsigned int block_h,
                const config &iconfig);
        ~shot_detector ();
        void restart (const unsigned char *first_frame, const unsigned int first_ts);
        shot flush ();
        shot detect (const unsigned char *curr_frame, const unsigned int curr_ts);
        void reset_config (const config &iconfig);
        void print_status ();

    private:
        shot_boundary_detector _sbd;
        status _status;
        shot _prev_shot;
        unsigned int _prev_boundary_ts;
        frametype _prev_boundary_type;
        bool _black_skipping;
        unsigned int _black_start;
        unsigned int _curr_ts;
        unsigned int _prev_ts;
        unsigned int _prev_prev_ts;
        float _shot_avg;
        float _shot_var;
        int _shot_num;
        bool _stared;
        unsigned int _min_len;
        std::vector<frame_info> _boundaries_cache;
        void do_detect (const unsigned char *curr_frame, unsigned int curr_ts);
        void update_status ();
};

#endif
