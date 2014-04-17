/**
 * @file AddingImages.cpp
 * @brief Simple linear blender ( dst = alpha*src1 + beta*src2 )
 * @author OpenCV team
 */

#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;

/**
 * @function main
 * @brief Main function
 */

int main ( int argc, char *argv[] )
{

   double alpha = 0.5; double beta; double input;

   Mat src1, src2, dst;


   // We use the alpha provided by the user iff it is between 0 and 1

   /// Read image ( same size, same type )
   //src1 = imread("../images/LinuxLogo.jpg");
   //src2 = imread("../images/WindowsLogo.jpg");
   src1 = imread(argv[1]);
   src2 = imread(argv[2]);

   if( !src1.data ) { std::cout<< "Error loading src1"<<std::endl; return -1; }
   if( !src2.data ) { std::cout<< "Error loading src2"<<std::endl; return -1; }

   /// Create Windows
   namedWindow("Linear Blend", 1);

   beta = ( 1.0 - alpha );
   addWeighted( src1, alpha, src2, beta, 0.0, dst);

   imshow( "Linear Blend", dst );


   waitKey(0);
   return 0;
}
