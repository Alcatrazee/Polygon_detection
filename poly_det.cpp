#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
  Mat img = imread("test_picture.jpg");
  Mat gray;
  Mat out_bin;
  Mat contour_out = Mat::zeros(img.size(),CV_8UC3);
  Scalar color(0,0,255);
  vector<Vec4i> hierarchy;
  vector<vector<Point> > contours;
  vector<vector<Point> > rects_ploy(contours.size());

  cvtColor(img, gray, COLOR_BGR2GRAY);
  threshold(gray, out_bin, 150, 255, THRESH_BINARY_INV);
  /* Canny(out_bin,out_bin,3,9,3); */
  findContours(out_bin, contours, hierarchy, CV_RETR_CCOMP,
               CV_CHAIN_APPROX_SIMPLE );
  double epsilon = 0.01 * arcLength(contours[0],true);
  approxPolyDP(contours[0], rects_ploy,15,true); 
  drawContours(contour_out,rects_ploy,0,color,2,8,hierarchy);
  
  imshow("img", contour_out);
  cout << contours.size()<<endl; 
  cout << epsilon<<endl;
  waitKey(0);
  return 0;
}