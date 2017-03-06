#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <cstdlib>
//#include <stdio.h>

using namespace std;
using namespace cv;
////////////////////////////////////////////////
int threshold_value = 0;
int threshold_type = 3;;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;
double pixel_value;
  double mini=1020, maxi=1020;
  int x, y, i, j; 

// Initialization of image2[y][x]
//Mat src, image2, image3;
char const* FINAL_WINDOW = "FINAL_WINDOW";

//char const* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
//char const* trackbar_value = "Value";
Mat image,image2,image3;

/*void Threshold_Demo( int, void* )
{
  /* 0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
   */
  /*threshold( image2, image3,threshold_value,max_BINARY_value,threshold_type);
      imshow( FINAL_WINDOW, image3 );
}*/
//////////////////////////////////////////////////


int main(int argc,char** arg){
	int dX[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
	int dY[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
	
	image = imread(arg[1]);
	namedWindow("STAGE 1",CV_WINDOW_NORMAL);
	imshow("STAGE 1",image);
	
	cvtColor(image,image2,CV_BGR2GRAY);

	long long int numRows = image.rows,numColumns = image.cols;
	
	namedWindow("STAGE 2",CV_WINDOW_NORMAL);
	cout<<"Image size : "<<numRows<<" * "<<numColumns<<endl;
	imshow("STAGE 2",image2);

	//namedWindow("FINAL_WINDOW",CV_WINDOW_NORMAL);
	image3 = image2.clone();

	//	img.at<uchar>(y, x) = 128;
	//creating a trackbar
////////////////////////////////////////////
 /*	createTrackbar( trackbar_type,
                  FINAL_WINDOW, &threshold_type,
                  max_type, Threshold_Demo );

  	createTrackbar( trackbar_value,
                  FINAL_WINDOW, &threshold_value,
                  max_value, Threshold_Demo );

  	Threshold_Demo( 0, 0 );   */
/////////////////////////////////// /////////////

  	//int grad1,grad11,grad2,grad22,grad3,grad33,grad4,grad44;
                  int x_size1,y_size1;
int x_size2 = x_size1=25;      //numRows;
int   y_size2 = y_size1=25;    //numColumns;
  //	namedWindow("OUTPUT",CV_WINDOW_NORMAL);
  //	Mat image3 = image2.clone();
  	cout<<"Now, filtering of input image is performed\n\n";
  
  for (y = 1; y < y_size1 - 1; y++) {
    for (x = 1; x < x_size1 - 1; x++) {
      pixel_value = 0.0;
      cout<< "val= "<<(int)image2.at<uchar>(y,x)<<endl;
      for (j = -1; j <= 1; j++) {
	    for (i = -1; i <= 1; i++) {
	      pixel_value += dX[j + 1][i + 1] * image2.at<uchar>(y,x) ;
	    }
      }
      if (pixel_value < mini) mini = pixel_value;
      if (pixel_value > maxi) maxi = pixel_value;
    }
  }
  if ((int)(maxi - mini) == 0) {
    cout<<"Nothing exists!!!\n\n";
    exit(1);
  }
  	//cout<<"threshold "<<threshold<<" threshold_value "<<threshold_value<<endl;
  	
  for (y = 0; y < y_size2; y++) {
    for (x = 0; x < x_size2; x++) {
     image3.at<uchar>(y,x) = 0;
    }
  }
  /* Generation of image2 after linear transformtion */
  for (y = 1; y < y_size1 - 1; y++) {
    for (x = 1; x < x_size1 - 1; x++) {
      pixel_value = 0.0;
      for (j = -1; j <= 1; j++) {
	    for (i = -1; i <= 1; i++) {
	      pixel_value += dX[j + 1][i + 1] * (int)image2.at<uchar>(y+j,x+i);
	    }
      }
      pixel_value/=9;
      cout<< "pixel_value= "<<pixel_value<<endl;
      if(pixel_value>150)
      {
      	cout<< "##\n";
      	image3.at<uchar>(y,x) = 255;
      }
      
    }
  }
  imshow("OUTPUT",image3);
	waitKey(0);

	return 0;
}
