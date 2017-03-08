#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

/// Global variables

Mat src, src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
char* window_name = "Super";


/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
void CannyThreshold(int, void*)
{
  /// Reduce noise with a kernel 3x3
  blur( src_gray, detected_edges, Size(kernel_size,kernel_size) );

  /// Canny detector
  Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
  //cout<<lowThreshold<<"\n";
  imshow(window_name,detected_edges);
  long int l,r,i,j;
  l=src_gray.rows;
  r=src_gray.cols;
  for(i=0;i<20;i++)
  { for(j=0;j<20;j++)
      printf("%d ",detected_edges.at<uchar>(i,j));
    printf("\n");
  }
  printf("\n\n");
 
 }


int main( int argc, char** argv )
{
  
  src = imread( argv[1] );
  if( !src.data )
  { return -1; }

  

  /// Convert the image to grayscale
  cvtColor( src, src_gray, CV_BGR2GRAY );

  /// Create a window
  namedWindow( window_name, CV_WINDOW_NORMAL );

  /// Create a Trackbar for user to enter threshold
  createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );
  
 
  /// Show the image
  CannyThreshold(0, 0);
   
  waitKey(0);

  return 0;
  }