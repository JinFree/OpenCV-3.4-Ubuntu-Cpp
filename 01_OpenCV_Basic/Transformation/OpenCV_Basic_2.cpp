#include "opencv2/core.hpp"
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

string path = "";
string image = "Lenna.png";

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
	namedWindow(imageName, flag);
	cout << "Display "<< imageName << " Channel: " << image.channels() << endl;
	
    imshow(imageName, image);
	waitKey(0); 
}
Mat mergeChannel(vector<Mat> channels) {
	Mat result;
	merge(channels,result);
	return result;
}
vector<Mat> splitChannel(Mat image) {
	vector<Mat> channels;
	split(image, channels);
	return channels;
}
void splitChannel(string imageName, Mat image) {
	vector<Mat> channels;
	channels = splitChannel(image);
	imageShow(imageName+"_0", channels[0], CV_WINDOW_NORMAL);
	imageShow(imageName+"_1", channels[1], CV_WINDOW_NORMAL);
	imageShow(imageName+"_2", channels[2], CV_WINDOW_NORMAL);
	Mat mergeResult = mergeChannel(channels);
	imageShow(imageName+"_merge", mergeResult, CV_WINDOW_NORMAL);
}
Mat colorSpace(string imageName, Mat image, int flag) {
	Mat dst;
	cvtColor(image, dst, flag);
	if(dst.channels() != 1) {
		splitChannel(imageName, dst);
	}
	else {
		imageShow("GrayScale", dst, CV_WINDOW_NORMAL);
	}
	return dst;
}
int main(void) {
    string openPath = path + image;
	Mat lennaBGR = imageRead(openPath, IMREAD_COLOR);
	imageShow("lennaBGR", lennaBGR, CV_WINDOW_NORMAL);
	
	cout << "CV_BGR2GRAY" << endl;
	Mat lennaGray = colorSpace("CV_BGR2GRAY", lennaBGR, CV_BGR2GRAY);
	imageShow("lennaGray", lennaGray, CV_WINDOW_NORMAL);
	
	cout << "CV_BGR2HSV" << endl;
	Mat lennaHSV = colorSpace("CV_BGR2HSV", lennaBGR, CV_BGR2HSV);
	imageShow("lennaHSV", lennaHSV, CV_WINDOW_NORMAL);
	
	cout << "CV_BGR2YUV" << endl;
	Mat lennaYUV = colorSpace("CV_BGR2YUV", lennaBGR, CV_BGR2YUV);
	imageShow("lennaYUV", lennaYUV, CV_WINDOW_NORMAL);
	
	cout << "CV_BGR2Lab" << endl;
	Mat lennaLAB = colorSpace("CV_BGR2Lab", lennaBGR, CV_BGR2Lab);
	imageShow("lennaLAB", lennaLAB, CV_WINDOW_NORMAL);
	
	destroyAllWindows();
	
	return 0;
}
