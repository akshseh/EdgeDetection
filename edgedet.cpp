//edge detect traversing

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
//#include <stdlib.h>

using namespace std;
using namespace cv;

Mat img,img2,img3,img4;
  long int l,r,i,j;
  int t;

void detect(int,void*)
{
    img2=img.clone();
    img3=img.clone();
    img4=img.clone();
   // img5=img.clone();
   for(int y=0;y<r;y++)
    {
        for(int x=0;x<l-1;x++)
        {
        
	  if(img.at<uchar>(x,y)-img.at<uchar>(x+1,y)>=t|| img.at<uchar>(x+1,y)-img.at<uchar>(x,y)>=t)//comparing pixels horizontally
          img2.at<uchar>(x,y) = 0;
        else img2.at<uchar>(x,y) =255;
      
      }
    }
    
    for(int y=0;y<r-1;y++)
    {
        for(int x=0;x<l;x++)
        {
        
	  if(img.at<uchar>(x,y)-img.at<uchar>(x,y+1)>=t|| img.at<uchar>(x,y+1)-img.at<uchar>(x,y)>=t)//comparing images vertically
          img3.at<uchar>(x,y) = 0;
        else img3.at<uchar>(x,y) =255;
      
      }
    }
    int chk1=255,chk2=0;
    for(int y=0;y<r;y++)
    {
        for(int x=0;x<l;x++)
        {
           
        if(img3.at<uchar>(x,y)==chk1 || img3.at<uchar>(x,y)==chk1)
          img4.at<uchar>(x,y) = chk1;
        else img4.at<uchar>(x,y) = chk2;
      
      }
    }
 

   imshow("hello1",img);
   //imshow("hello2",img2);
   //imshow("hello3",img3);
   imshow("hello4",img4);
    
}
int main(int argc,char** arg)
{
	img=imread(arg[1]);
	namedWindow( "hello1", CV_WINDOW_NORMAL);
	

	cvtColor(img,img,CV_BGR2GRAY);

	//namedWindow("hello2",CV_WINDOW_NORMAL);
	//namedWindow("hello3",CV_WINDOW_NORMAL);
	namedWindow("hello4",CV_WINDOW_NORMAL);
  //namedWindow("hello5",CV_WINDOW_NORMAL);
	

	l=img.rows;
	r=img.cols;
	cout<<l<<" "<<r<<endl;
  cout<<img.channels()<<endl;
 
//	cout<<l<<" "<<r<<endl;
  // threshold=10;
  const int max=100;


  createTrackbar("threshold","hello4",&t,max,detect);
  detect(0,0);
   
	waitKey(0);
	return 0;
}
