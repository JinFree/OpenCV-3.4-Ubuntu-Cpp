#pragma once
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

string path = "../../Data/";
string lennaImage = "Lenna_Images/Lenna.png";
string roadImage = "Lane_Detection_Images/test.jpg";

Mat thresholdByAt(Mat image, uchar thresh = 128);
Mat thresholdByPtr(Mat image, uchar thresh = 128);
Mat thresholdByData(Mat image, uchar thresh = 128);
Mat imageRead(string openPath, int flag = IMREAD_UNCHANGED);
void imageShow(string imageName, Mat image, int flag = CV_WINDOW_NORMAL);

Mat thresholdByAt(Mat image, uchar thresh) {
	int i,j;
	Mat result = image.clone();
	if(result.type() == CV_8UC1) {
		for( j = 0 ; j < result.rows ; j++) {
			for ( i = 0 ; i < result.cols ; i++ ) {
				uchar value = result.at<uchar>(j,i);
				value = value > thresh ? 255 : 0;
				result.at<uchar>(j,i) = value;
			}
		}
	}
	else if(result.type() == CV_8UC3) {
		for( j = 0 ; j < result.rows ; j++) {
			for ( i = 0 ; i < result.cols ; i++ ) {
				Vec3b value = result.at<Vec3b>(j, i);
				int c;
				for(c = 0 ; c < 3 ; c++) {
					value[c] = value[c] > thresh ? 255 : 0;
				}
				result.at<Vec3b>(j,i) = value;
			}
		}
	}
	return result;
}
Mat thresholdByPtr(Mat image, uchar thresh) {
	int i,j;
	Mat result = image.clone();
	if(result.type() == CV_8UC1) {
		for( j = 0 ; j < result.rows ; j++) {
			uchar* image_pointer = result.ptr<uchar>(j);
			for ( i = 0 ; i < result.cols ; i++ ) {
				uchar value = image_pointer[i];
				value = value > thresh ? 255 : 0;
				image_pointer[i] = value;
			}
		}
	}
	else if(result.type() == CV_8UC3) {
		for( j = 0 ; j < result.rows ; j++) {
			uchar* image_pointer = result.ptr<uchar>(j);
			for ( i = 0 ; i < result.cols ; i++ ) {
				int c;
				for(c = 0 ; c < 3 ; c++) {
					uchar value = image_pointer[i*3+c];
					value = value > thresh ? 255 : 0;
					image_pointer[i*3+c] = value;
				}
			}
		}
	}
	return result;
}
Mat thresholdByData(Mat image, uchar thresh) {
	int i,j;
	Mat result = image.clone();
	uchar *image_data = result.data;
	if(result.type() == CV_8UC1) {
		for( j = 0 ; j < result.rows ; j++) {
			for ( i = 0 ; i < result.cols ; i++ ) {
				uchar value = image_data[j * result.cols + i];
				value = value > thresh ? 255 : 0;
				image_data[j * result.cols + i] = value;
			}
		}
	}
	else if(result.type() == CV_8UC3) {
		for( j = 0 ; j < result.rows ; j++) {
			for ( i = 0 ; i < result.cols ; i++ ) {
				int c;
				for(c = 0 ; c < 3 ; c++) {
					uchar value = image_data[(j * result.cols + i) * 3 + c];
					value = value > thresh ? 255 : 0;
					image_data[(j * result.cols + i) * 3 + c] = value;
				}
			}
		}
	}
	return result;
}
Mat imageRead(string openPath, int flag) {
	Mat image = imread(openPath, flag);
	if(image.empty()) {
		cout<<"Image Not Opened"<<endl;
		cout<<"Program Abort"<<endl;
		exit(1);
	}
	else {
		cout<<"Image Opened"<<endl;
		return image;
	}
}
void imageShow(string imageName, Mat image, int flag) {
    cout << "Display "<< imageName << " Channel: " << image.channels() << endl;
	namedWindow(imageName, flag);
    imshow(imageName, image);
	waitKey(0);
}
