#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

string path = "../../Data/";
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
void savechannels(string path, string ImageName, string channelname, Mat image) {
	if(image.channels() != 1) {
		vector<Mat> channels;
		channels = splitChannel(image);
		int i;
		for( i = 0 ; i < 3 ; i++) {
			imwrite(path+ImageName+"_"+channelname[i]+".bmp", channels[i]);
		}
	}
	else {
		imwrite(path+ImageName+".bmp", image);
	}
	return;
}
int main(void) {
    string openPath = path + image;
	Mat LennaBGR = imageRead(openPath, IMREAD_COLOR);
	imageShow("LennaBGR", LennaBGR, CV_WINDOW_NORMAL);
	savechannels(path, "LennaBGR", "BGR", LennaBGR);

	cout << "CV_BGR2GRAY" << endl;
	Mat LennaGray = colorSpace("CV_BGR2GRAY", LennaBGR, CV_BGR2GRAY);
	imageShow("LennaGray", LennaGray, CV_WINDOW_NORMAL);
	savechannels(path, "LennaGray", "", LennaGray);

	cout << "CV_BGR2HSV" << endl;
	Mat LennaHSV = colorSpace("CV_BGR2HSV", LennaBGR, CV_BGR2HSV);
	imageShow("LennaHSV", LennaHSV, CV_WINDOW_NORMAL);
	savechannels(path, "LennaHSV", "HSV", LennaHSV);

	cout << "CV_BGR2YUV" << endl;
	Mat LennaYUV = colorSpace("CV_BGR2YUV", LennaBGR, CV_BGR2YUV);
	imageShow("LennaYUV", LennaYUV, CV_WINDOW_NORMAL);
	savechannels(path, "LennaYUV", "YUV", LennaYUV);

	cout << "CV_BGR2Lab" << endl;
	Mat LennaLAB = colorSpace("CV_BGR2Lab", LennaBGR, CV_BGR2Lab);
	imageShow("LennaLAB", LennaLAB, CV_WINDOW_NORMAL);
	savechannels(path, "LennaLAB", "LAB", LennaLAB);

	destroyAllWindows();
	return 0;
}
