#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

string path = "../../Data/Lenna_Images/";
string image = "Lenna.png";

Mat imageRead(string openPath, int flag = IMREAD_UNCHANGED);
void imageShow(string imageName, Mat image, int flag = CV_WINDOW_NORMAL);
Mat createMat(int height = 200, int width = 400, int flag = CV_8UC3, Scalar value = Scalar(0,0,255));
Mat createMat(int height = 200, int width = 400, int flag = CV_8U, int value = 128);

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
Mat createMat(int height, int width, int flag, Scalar value) {
	Mat result(height, width, flag, value);
	return result;
}

Mat createMat(int height, int width, int flag, int value) {
	Mat result(height, width, flag, value);
	return result;
}
