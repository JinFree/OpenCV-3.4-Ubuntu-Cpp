#include "OpenCV.h"

using namespace std;
using namespace cv;

string path = "../../Data/";
string lennaImage = "Lenna_Images/Lenna.png";
string roadImage = "Lane_Detection_Images/solidYellowLeft.jpg";
string sudokuImage = "sudoku-original.jpg";

int main(void) {
	double timer;
	string openPath = path + sudokuImage;
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

	imageShow("sudokuGray", sudokuGray);
	imwrite(path+"sudoku-sudokuGray.jpg", sudokuGray);

	Mat CV_Gray_THRESH_BINARY = thresholdByCV(sudokuGray, 128, 255, THRESH_BINARY);
	imageShow("CV_Gray_THRESH_BINARY", CV_Gray_THRESH_BINARY);
	imwrite(path+"sudoku-CV_Gray_THRESH_BINARY.jpg", CV_Gray_THRESH_BINARY);

	Mat CV_Gray_THRESH_BINARY_INV = thresholdByCV(sudokuGray, 128, 255, THRESH_BINARY_INV);
	imageShow("CV_Gray_THRESH_BINARY_INV", CV_Gray_THRESH_BINARY_INV);
	imwrite(path+"sudoku-CV_Gray_THRESH_BINARY_INV.jpg", CV_Gray_THRESH_BINARY_INV);

	Mat CV_Gray_THRESH_TRUNC = thresholdByCV(sudokuGray, 128, 255, THRESH_TRUNC);
	imageShow("CV_Gray_THRESH_TRUNC", CV_Gray_THRESH_TRUNC);
	imwrite(path+"sudoku-CV_Gray_THRESH_TRUNC.jpg", CV_Gray_THRESH_TRUNC);

	Mat CV_Gray_THRESH_TOZERO = thresholdByCV(sudokuGray, 128, 255, THRESH_TOZERO);
	imageShow("CV_Gray_THRESH_TOZERO", CV_Gray_THRESH_TOZERO);
	imwrite(path+"sudoku-CV_Gray_THRESH_TOZERO.jpg", CV_Gray_THRESH_TOZERO);

	Mat CV_Gray_THRESH_TOZERO_INV = thresholdByCV(sudokuGray, 128, 255, THRESH_TOZERO_INV);
	imageShow("CV_Gray_THRESH_TOZERO_INV", CV_Gray_THRESH_TOZERO_INV);
	imwrite(path+"sudoku-CV_Gray_THRESH_TOZERO_INV.jpg", CV_Gray_THRESH_TOZERO_INV);

	Mat CV_Gray_AdaptiveThreshold_MEAN = adaptiveThresholdByCV(sudokuGray, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, 0);
	imageShow("CV_Gray_AdaptiveThreshold_MEAN", CV_Gray_AdaptiveThreshold_MEAN);
	imwrite(path+"sudoku-CV_Gray_AdaptiveThreshold_MEAN.jpg", CV_Gray_AdaptiveThreshold_MEAN);

	Mat CV_Gray_AdaptiveThreshold_GAUSSIAN = adaptiveThresholdByCV(sudokuGray, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 3, 0);
	imageShow("CV_Gray_AdaptiveThreshold_GAUSSIAN", CV_Gray_AdaptiveThreshold_GAUSSIAN);
	imwrite(path+"sudoku-CV_Gray_AdaptiveThreshold_GAUSSIAN.jpg", CV_Gray_AdaptiveThreshold_GAUSSIAN);

	destroyAllWindows();

	return 0;
}

#ifdef OPENCV_H_
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
    cout << "Display "<< imageName << " Channel: " << image.channels() << endl;
	namedWindow(imageName, flag);
    imshow(imageName, image);
	waitKey(0);
}
#endif
