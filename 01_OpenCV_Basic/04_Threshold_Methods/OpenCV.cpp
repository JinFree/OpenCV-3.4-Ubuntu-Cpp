#include "OpenCV.h"

using namespace std;
using namespace cv;

int main(void) {
	double timer;
	string openPath = path + image;
	Mat sudokuColor = imageRead(openPath, IMREAD_COLOR);
	imageShow("sudokuColor", sudokuColor);

	Mat sudokuGray = imageRead(openPath, IMREAD_GRAYSCALE);
	imageShow("sudokuGray", sudokuGray);

	timer = (double)getTickCount();
	Mat ByPtr_Gray = thresholdByPtr(sudokuGray, 128);
	timer = ((double)getTickCount() - timer) / getTickFrequency();
	cout << "threshold gray time ptr =  " << timer << " sec" << endl;
	imageShow("ByPtr_Gray", ByPtr_Gray);

	timer = (double)getTickCount();
	Mat ByPtr_Color = thresholdByPtr(sudokuColor, 128);
	timer = ((double)getTickCount() - timer) / getTickFrequency();
	cout << "threshold color time ptr =  " << timer << " sec" << endl;
	imageShow("ByPtr_Color", ByPtr_Color);

	timer = (double)getTickCount();
	Mat ByCV_Gray = thresholdByCV(sudokuGray, 128);
	timer = ((double)getTickCount() - timer) / getTickFrequency();
	cout << "threshold gray time cv =  " << timer << " sec" << endl;
	imageShow("ByCV_Gray", ByCV_Gray);

	timer = (double)getTickCount();
	Mat ByCV_Color = thresholdByCV(sudokuColor, 128);
	timer = ((double)getTickCount() - timer) / getTickFrequency();
	cout << "threshold color time cv =  " << timer << " sec" << endl;
	imageShow("ByCV_Color", ByCV_Color);

	destroyAllWindows();

	Mat CV_Gray_THRESH_BINARY = thresholdByCV(sudokuGray, 128, 255, THRESH_BINARY);
	imageShow("CV_Gray_THRESH_BINARY", CV_Gray_THRESH_BINARY);

	Mat CV_Gray_THRESH_BINARY_INV = thresholdByCV(sudokuGray, 128, 255, THRESH_BINARY_INV);
	imageShow("CV_Gray_THRESH_BINARY_INV", CV_Gray_THRESH_BINARY_INV);

	Mat CV_Gray_THRESH_TRUNC = thresholdByCV(sudokuGray, 128, 255, THRESH_TRUNC);
	imageShow("CV_Gray_THRESH_TRUNC", CV_Gray_THRESH_TRUNC);

	Mat CV_Gray_THRESH_TOZERO = thresholdByCV(sudokuGray, 128, 255, THRESH_TOZERO);
	imageShow("CV_Gray_THRESH_TOZERO", CV_Gray_THRESH_TOZERO);

	Mat CV_Gray_THRESH_TOZERO_INV = thresholdByCV(sudokuGray, 128, 255, THRESH_TOZERO_INV);
	imageShow("CV_Gray_THRESH_TOZERO_INV", CV_Gray_THRESH_TOZERO_INV);

	destroyAllWindows();

	Mat CV_Gray_THRESH_BINARY = thresholdByCV(sudokuGray, 128, 255, THRESH_BINARY);
	imageShow("CV_Gray_THRESH_BINARY", CV_Gray_THRESH_BINARY);

	
	destroyAllWindows();

	return 0;
}