#ifndef _SHOT_DETECT_H_
#define _SHOT_DETECT_H_

enum frametype {NORMAL, BOUNDARY, BLACK};

struct frame_info 
{
    unsigned int avg;
    unsigned int var;
    frametype frame_type; //0 for not boundary, 1 for boundary, 2 for black frame
    unsigned int prev_ts;
    unsigned int cut;
};

class shot_boundary_detector 
{ 
    public:
        //constructor. init memory 
        shot_boundary_detector (const unsigned int width, 
                                const unsigned int height, 
                                const unsigned int block_w, 
                                const unsigned int block_h,
                                const float hist_th, 
                                const int diff_cnt_th, 
                                const float var_th);
        shot_boundary_detector (const shot_boundary_detector &other);
        shot_boundary_detector &operator = (const shot_boundary_detector &other);
        //destructor, free memory
        ~shot_boundary_detector (); 
        //restart detection, push the first frame buffer
        void start (const unsigned char *first_frame_buffer, 
                    const unsigned int first_ts); 
        frame_info detect (const unsigned char *current_frame_buffer, 
                            const unsigned int curr_ts); 
        void reset_config (const float hist_th, const int diff_cnt_th, 
                            const float var_th);
        bool check_params ();
    private:
        unsigned int _width;
        unsigned int _height;
        unsigned int _block_w;
        unsigned int _block_h; 
        float _hist_th;
        int _diff_cnt_th;
        float _var_th;
        float _avg_th;

        unsigned int **_prev_frame_hist;
        unsigned int **_curr_frame_hist;
        bool _started;
        unsigned int *_hist_num;
        bool _prev_black;
        unsigned int _prev_ts;
        float _prev_var;
        float _prev_avg;
        unsigned int _prev_cut;

};

#endif
