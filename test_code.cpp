#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

void Polygon_detection(Mat &srcImg,Mat &dstImg,vector<Point2f> &out_mc,vector<int> &shape){
  cvtColor(srcImg, srcImg, CV_BGR2GRAY);
  threshold(srcImg, srcImg, 200, 255, CV_THRESH_BINARY_INV);

  vector<vector<Point> > contours;
  vector<Vec4i> hierarcy;
  findContours(srcImg, contours, hierarcy, 0, CV_CHAIN_APPROX_NONE);


  vector<Moments>mu(contours.size());
  vector<vector<Point> > contours_poly(contours.size()); 
  vector<Point2f>mc(contours.size());

  for (int i = 0; i < contours.size(); i++) {
    double epsilon = 0.01 * arcLength(contours[i], true);
    approxPolyDP(Mat(contours[i]), contours_poly[i], epsilon, true);
    drawContours(dstImg, contours_poly, i, Scalar(0, 255, 255), 2, 8); 
    mu[i] = moments(contours_poly[i], false);
    mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
    circle(dstImg, mc[i], 4, Scalar(255,0,0), -1, 8, 0);  
    out_mc.push_back(mc[i]);
    shape.push_back((int)contours_poly[i].size());
  }

}

int main() {
  Mat srcImg = imread("test_pic.png");
  Mat dstImg(srcImg.size(), CV_8UC3, Scalar::all(0)); //纯黑图像
  vector<Point2f>mc;
  vector<int> shape;
  Polygon_detection(srcImg,dstImg,mc,shape);

  for (int i=0;i<shape.size();i++){
    switch(shape[i]){
      case 3:
        cout<< "Triangle:position:(";
      break;
      case 4:
        cout<< "Rectangle:position:(";
      break;
      case 5:
        cout<< "Pentagon:position:(";
      break;
      case 6:
        cout<< "Hexagon:position:(";
      break;
      default:
        cout<< "Circle:position:(";
    }
    cout<<mc[i]<<")"<<endl;
  }

  imshow("approx", dstImg);
  waitKey(0);
  return 0;
}