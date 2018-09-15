#pragma once
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

string path = "../../Data/";
string lennaImage = "Lenna_Images/Lenna.png";
string roadImage = "Lane_Detection_Images/test.jpg";

Mat clippedHistogramEqualize(Mat image, double clipLimit = 40.0, Size tileGridSize = Size(4,4));
Mat histogramEqualize(Mat image);
Mat bilateralFilter(Mat image, int d = -1, double sigmaColor = 5.0, double sigmaSpace = 5.0, int borderType = BORDER_DEFAULT);
Mat medianBlur(Mat image, int kernelSize = 5);
Mat gaussianBlur(Mat image, Size kernelSize = Size(5,5), double sigmaX = 2, double sigmaY = 0, int	borderType = BORDER_DEFAULT);
Mat meanBlur(Mat image, Size kernelSize = Size(5,5), Point anchor = Point(-1,-1), int borderType = BORDER_DEFAULT);
Mat addSaltAndPepper(Mat image, double noiseRatio = 0.01);
Mat mergeChannel(Mat ch1, Mat ch2, Mat ch3);
Mat mergeChannel(vector<Mat> channels);
vector<Mat> splitChannel(Mat image);
Mat convertColor(Mat image, int flag = CV_BGR2GRAY);
void showChannels(string imageName, Mat image);
void saveChannels(string path, string ImageName, string channelname, Mat image);
Mat adaptiveThresholdByCV(Mat image, double maxValue = 255, int adaptiveMethod = ADAPTIVE_THRESH_GAUSSIAN_C, int thresholdType = THRESH_BINARY, int blockSize = 3, double C = 0);
Mat thresholdByCV(Mat image, double thresh = 128, double maxval = 255, int type = THRESH_BINARY);
Mat thresholdByAt(Mat image, uchar thresh = 128);
Mat thresholdByPtr(Mat image, uchar thresh = 128);
Mat thresholdByData(Mat image, uchar thresh = 128);
Mat imageRead(string openPath, int flag = IMREAD_UNCHANGED);
void imageShow(string imageName, Mat image, int flag = CV_WINDOW_NORMAL);

Mat clippedHistogramEqualize(Mat image, double clipLimit, Size tileGridSize) {
	Mat result;
	cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
	clahe->setClipLimit(clipLimit);
	clahe->setTilesGridSize(tileGridSize);
	clahe->apply(image, result);
	return result;
}
Mat histogramEqualize(Mat image) {
	Mat result;
	equalizeHist(image, result);
	return result;
}
Mat bilateralFilter(Mat image, int d, double sigmaColor, double sigmaSpace, int borderType) {
	Mat result;
	bilateralFilter(image, result, d, sigmaColor, sigmaSpace, borderType);
	return result;
}
Mat medianBlur(Mat image, int kernelSize) {
	Mat result;
	medianBlur(image, result, kernelSize);
	return result;
}
Mat gaussianBlur(Mat image, Size kernelSize, double sigmaX, double sigmaY, int borderType) {
	Mat result;
	GaussianBlur(image, result, kernelSize, sigmaX, sigmaY, borderType);
	return result;
}
Mat meanBlur(Mat image, Size kernelSize, Point anchor, int borderType) {
	Mat result;
	blur(image, result, kernelSize, anchor, borderType);
	return result;
}
Mat addSaltAndPepper(Mat image, double noiseRatio) {
	Mat result = image.clone();
	int i;
	int rows = result.rows;
	int cols = result.cols;
	int ch = result.channels();
	int num_of_noise_pixels = (int)((double)(rows*cols*ch)*noiseRatio);
	for ( i = 0 ; i < num_of_noise_pixels ; i++ ){
		int r = rand() % rows;
		int c = rand() % cols;
		int _ch = rand() % ch;

		uchar* pixel = result.ptr<uchar>(r)+(c*ch)+_ch;
		*pixel = (rand()%2==1)?255:0;
	}
	return result;
}
Mat mergeChannel(Mat ch1, Mat ch2, Mat ch3) {
	Mat result;
	vector<Mat> channels;
	channels.push_back(ch1);
	channels.push_back(ch2);
	channels.push_back(ch3);
	merge(channels, result);
	return result;
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
Mat convertColor(Mat image, int flag) {
	Mat result;
	cvtColor(image, result, flag);
	return result;
}
void showChannels(string imageName, Mat image) {
	if(image.channels() != 1) {
		vector<Mat> channels;
		channels = splitChannel(image);
		imageShow(imageName+"_0", channels[0]);
		imageShow(imageName+"_1", channels[1]);
		imageShow(imageName+"_2", channels[2]);
	}
	else if(image.channels() == 1){
		imageShow("GrayScale", image);
	}
	return;
}
void saveChannels(string path, string ImageName, string channelname, Mat image) {
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
Mat adaptiveThresholdByCV(Mat image, double maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C ) {
	Mat result;
	adaptiveThreshold(image, result, maxValue, adaptiveMethod, thresholdType, blockSize, C);
	return result;
}
Mat thresholdByCV(Mat image, double thresh, double maxval, int type) {
	Mat result;
	threshold(image, result, thresh, maxval, type);
	return result;
}
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
	namedWindow(imageName, flag);
	cout << "Display "<< imageName << " Channel: " << image.channels() << endl;
    imshow(imageName, image);
	waitKey(0);
}
