#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

string path = "../../Data/Lenna_Images/";
string image = "Lenna.png";

Mat imageRead(string openPath, int flag = IMREAD_UNCHANGED);
void imageShow(string imageName, Mat image, int flag = CV_WINDOW_NORMAL);
Mat thresholdByAt(Mat image, uchar threshold = 128);
Mat thresholdByPtr(Mat image, uchar threshold = 128);
Mat thresholdBtData(Mat image, uchar threshold = 128);
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
Mat thresholdByAt(Mat image, uchar threshold) {
	int i,j;
	if(image.type() == CV_8UC1) {
		for ( i = 0 ; i < image.cols() ; i++ ) {
			for( j = 0 ; j < image.rows() ; j++) {
				uchar value = image.at<uchar>(j,i);
				value = value > threshold ? 255 : 0;
				image.at<uchar>(j,i) = value;
			}
		}
	}
	return image;
}
Mat thresholdByPtr(Mat image, uchar threshold) {

	return image;
}
Mat thresholdBtData(Mat image, uchar threshold) {
	return image;
}
