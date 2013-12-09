<<<<<<< HEAD
g++ -g test_video_split.cpp video_split.cpp libshot_detector.a -o test
=======
rm test
g++ -g test_video_split.cpp video_split.cpp shot_boundary_detect.cpp shot_detector.cpp -o test
>>>>>>> 436fdfef693cf026f04e18bcebb8ff4fe0b1b6f2
