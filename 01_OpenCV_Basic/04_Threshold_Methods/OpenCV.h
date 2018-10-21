#ifndef OPENCV_H_
#define OPENCV_H_
#endif //OPENCV_H_
#pragma once
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

Mat adaptiveThresholdByCV(Mat image, double maxValue = 255, int adaptiveMethod = ADAPTIVE_THRESH_GAUSSIAN_C, int thresholdType = THRESH_BINARY, int blockSize = 3, double C = 0);
Mat thresholdByCV(Mat image, double thresh = 128, double maxval = 255, int type = THRESH_BINARY);
Mat thresholdByAt(Mat image, uchar thresh = 128);
Mat thresholdByPtr(Mat image, uchar thresh = 128);
Mat thresholdByData(Mat image, uchar thresh = 128);
Mat imageRead(string openPath, int flag = IMREAD_UNCHANGED);
void imageShow(string imageName, Mat image, int flag = CV_WINDOW_NORMAL);
