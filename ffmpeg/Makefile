BASE_DIR=..
INC_DIR=$(BASE_DIR)/include
LIB_DIR=$(BASE_DIR)/lib

CXX=gcc

LIBS=-pthread -lavdevice -lavformat -lavfilter -lz -lbz2 -ldl -lavcodec -lswscale -lm -lavutil -lmp3lame -lfaac -lgsm -lopencore-amrnb -lopencore-amrwb

audio_convertor: audio_convertor.c
	$(CXX) -o $@ $< -I$(INC_DIR) -L$(LIB_DIR) $(LIBS)
