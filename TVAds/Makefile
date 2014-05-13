.PHONY: deinterlace
.LIBPATTERNS = lib%.a lib%.so

VPATH =  .:./fingerprint/lib:./idnagen_lib/lib

CC = g++
#CPPFLAGS := ${CPPFLAGS} -g -I. -I../ -Wall -I/usr/include/inotifytools/ -I../capture/lib/DeckLink/include/ -I./adnagenr70222

# code coverage test
ifeq ($(TEST_COVERAGE), on) 
    CPPFLAGS += -fprofile-arcs -ftest-coverage
    LDFLAGS += -fprofile-arcs
endif

ifeq ($(NEW_AUDIO_DNA), false)
CPPFLAGS := ${CPPFLAGS} -g -D__STDC_CONSTANT_MACROS -I. -I../ -I./include -Wall -I/usr/include/inotifytools/ -I../capture/lib/DeckLink/include/ -I./adnagenr70222
LIBS = ./fingerprint/lib/libfingerprint.a ./fingerprint/lib/libjpeg_linux.a ./fingerprint/lib/libsamplerate_linux.a ./idnagen_lib/lib/libidnagen.a ./idnagen_lib/lib/libencfile1_linux.a ./idnagen_lib/lib/libxfp_linux32.a idnagen_lib/lib/libcvaux.so.4 idnagen_lib/lib/libcv.so.4 idnagen_lib/lib/libcxcore.so.4 idnagen_lib/lib/libhighgui.so.4 idnagen_lib/lib/libml.so.4 idnagen_lib/lib/libpng12.so.0 idnagen_lib/lib/libtiff.so.4 deinterlace/libavpreprocesser.a ./lib/libFLAC.so.8 ./adnagenr70222/lib/libavcodec.a ./adnagenr70222/lib/libavutil.a ./lib/libshot_detector.a
else
CPPFLAGS := ${CPPFLAGS} -g -DNEW_AUDIO_DNA -D__STDC_CONSTANT_MACROS -I. -I../  -I./include -Wall -I/usr/include/inotifytools/ -I../capture/lib/DeckLink/include/ -I./adnagenr70222
LIBS = ./fingerprint/lib/libfingerprint.a ./fingerprint/lib/libjpeg_linux.a ./fingerprint/lib/libsamplerate_linux.a ./idnagen_lib/lib/libidnagen.a ./idnagen_lib/lib/libencfile1_linux.a ./idnagen_lib/lib/libxfp_linux32.a idnagen_lib/lib/libcvaux.so.4 idnagen_lib/lib/libcv.so.4 idnagen_lib/lib/libcxcore.so.4 idnagen_lib/lib/libhighgui.so.4 idnagen_lib/lib/libml.so.4 idnagen_lib/lib/libpng12.so.0 idnagen_lib/lib/libtiff.so.4 deinterlace/libavpreprocesser.a ./adnagenr70222/lib/libafp4_wrap.a ./adnagenr70222/lib/libavcodec.a ./adnagenr70222/lib/libavutil.a ./lib/libFLAC.so.8 ./lib/libshot_detector.a
endif

all: fingerprint deinterlace liveProcessor

clean:
	rm -rf *.o liveProcessor inotify.h
	rm -rf INIReader/*.o
	for file in *.py; do ./try.sed $$file >x ; cat x >$$file; rm x; done
	rm -rf *.pyc
	#rm -rf fingerprint
	cd deinterlace; $(MAKE) $@

liveProcessor : util.o INIReader/INIReader.o INIReader/ini.o video_split.o liveProcessor.o fileProcessor.o vfp.o afp.o main.o $(LIBS)

liveProcessor.cpp: inotify.h

inotify.h:
	@if [ -e /usr/include/sys/inotify.h ] ; then cp /usr/include/sys/inotify.h $@ ; fi

run:
	@-killall -9 liveProcessor
	@(./liveProcessor tmp tests/abc.jpg tests &)

debug: 
	for file in *.py; do ./notry.sed $$file >x ; cat x >$$file; rm x; done
fingerprint : 
	#tar zxf doc/fingerprint_linux_20091027.tar.gz
	tar zxf doc/fingerprint_linux_withedge.tar.gz

deinterlace: 
	cd $@; $(MAKE)
    
cctv:
	tar zcvf cctv.tar.gz liveMain_cctv.py add_cctv.sql delete_cctv.sql logging_cctv.conf

install:
	rm -rf /opt/rtfp/var/log/dnaUploader.log
	install dna_uploader.py /opt/rtfp/bin
	install Live/vddb_wget.py /opt/rtfp/bin/Live
	ps -ef |grep dna_uploader | grep -v grep | gawk '{print $$2}' | xargs -r kill -9
	sleep 3
	killall -9 liveProcessor

clangtest:
	clang -O3 -g -DNEW_AUDIO_DNA -D__STDC_CONSTANT_MACROS -I. -I../ -I./include -Wall -I/usr/include/inotifytools/ -I../capture/lib/DeckLink/include/ -I./adnagenr70222 liveProcessor.cpp fileProcessor.cpp vfp.cpp afp.cpp main.cpp util.cpp fingerprint/lib/libfingerprint.a fingerprint/lib/libjpeg_linux.a fingerprint/lib/libsamplerate_linux.a idnagen_lib/lib/libidnagen.a idnagen_lib/lib/libencfile1_linux.a idnagen_lib/lib/libxfp_linux32.a idnagen_lib/lib/libcvaux.so.4 idnagen_lib/lib/libcv.so.4 idnagen_lib/lib/libcxcore.so.4 idnagen_lib/lib/libhighgui.so.4 idnagen_lib/lib/libml.so.4 idnagen_lib/lib/libpng12.so.0 idnagen_lib/lib/libtiff.so.4 deinterlace/libavpreprocesser.a adnagenr70222/lib/libafp4_wrap.a adnagenr70222/lib/libavcodec.a adnagenr70222/lib/libavutil.a lib/libFLAC.so.8 -o liveProcessor -lstdc++ -lm

