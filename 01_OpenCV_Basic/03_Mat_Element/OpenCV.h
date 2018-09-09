#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

string path = "../../Data/Lenna_Images/";
string image = "Lenna.png";

Mat imageRead(string openPath, int flag = IMREAD_UNCHANGED);
void imageShow(string imageName, Mat image, int flag = CV_WINDOW_NORMAL);
Mat thresholdByAt(Mat image, uchar thresh = 128);
Mat thresholdByPtr(Mat image, uchar thresh = 128);
Mat thresholdByData(Mat image, uchar thresh = 128);

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
Mat thresholdByAt(Mat image, uchar thresh) {
	int i,j;
	if(image.type() == CV_8UC1) {
		for( j = 0 ; j < image.rows ; j++) {
			for ( i = 0 ; i < image.cols ; i++ ) {
				uchar value = image.at<uchar>(j,i);
				value = value > thresh ? 255 : 0;
				image.at<uchar>(j,i) = value;
			}
		}
	}
	else if(image.type() == CV_8UC3) {
		for( j = 0 ; j < image.rows ; j++) {
			for ( i = 0 ; i < image.cols ; i++ ) {
				Vec3b value = image.at<Vec3b>(j, i);
				int c;
				for(c = 0 ; c < 3 ; c++) {
					value[c] = value[c] > thresh ? 255 : 0;
				}
				image.at<Vec3b>(j,i) = value;
			}
		}
	}
	return image;
}
Mat thresholdByPtr(Mat image, uchar thresh) {
	int i,j;
	if(image.type() == CV_8UC1) {
		for( j = 0 ; j < image.rows ; j++) {
			uchar* image_pointer = image.ptr<uchar>(j);
			for ( i = 0 ; i < image.cols ; i++ ) {
				uchar value = image_pointer[i];
				value = value > thresh ? 255 : 0;
				image_pointer[i] = value;
			}
		}
	}
	else if(image.type() == CV_8UC3) {
		for( j = 0 ; j < image.rows ; j++) {
			uchar* image_pointer = image.ptr<uchar>(j);
			for ( i = 0 ; i < image.cols ; i++ ) {
				int c;
				for(c = 0 ; c < 3 ; c++) {
					uchar value = image_pointer[i*3+c];
					value = value > thresh ? 255 : 0;
					image_pointer[i*3+c] = value;
				}
			}
		}
	}
	return image;
}
Mat thresholdByData(Mat image, uchar thresh) {
	uchar *image_data = image.data;
	int i,j;
	if(image.type() == CV_8UC1) {
		for( j = 0 ; j < image.rows ; j++) {
			for ( i = 0 ; i < image.cols ; i++ ) {
				uchar value = image_data[j * image.cols + i];
				value = value > thresh ? 255 : 0;
				image_data[j * image.cols + i] = value;
			}
		}
	}
	else if(image.type() == CV_8UC3) {
		for( j = 0 ; j < image.rows ; j++) {
			for ( i = 0 ; i < image.cols ; i++ ) {
				int c;
				for(c = 0 ; c < 3 ; c++) {
					uchar value = image_data[(j * image.cols + i) * 3 + c];
					value = value > thresh ? 255 : 0;
					image_data[(j * image.cols + i) * 3 + c] = value;
				}
			}
		}
	}
	return image;
}
