#include "OpenCV.h"

using namespace std;
using namespace cv;

string path = "../../Data/";
string lennaImage = "Lenna_Images/Lenna.png";
string roadImage = "Lane_Detection_Images/solidYellowLeft.jpg";
string sudokuImage = "sudoku-original.jpg";

int main(void) {
	string openPath = path + sudokuImage;
	
	Mat sudokuColor = imageRead(openPath, IMREAD_COLOR);
	imageShow("sudokuColor", sudokuColor);

	Mat sudokuGray = imageRead(openPath, IMREAD_GRAYSCALE);
	imageShow("sudokuGray", sudokuGray);

	Mat ByCV_Gray = thresholdByCV(sudokuGray, 128);
	imageShow("ByCV_Gray", ByCV_Gray);

	Mat ByCV_Color = thresholdByCV(sudokuColor, 128);
	imageShow("ByCV_Color", ByCV_Color);

	destroyAllWindows();
	
	Mat ThresholdTest(512, 512, CV_8UC1, 128);
	int i,j;
	for( j = 0 ; j < ThresholdTest.rows ; j++) {
	uchar* image_pointer = ThresholdTest.ptr<uchar>(j);
	for ( i = 0 ; i < ThresholdTest.cols ; i++ ) {
		image_pointer[i] = i < 256 ? i : 256 - i;} }
	imageShow("ThresholdTest", ThresholdTest);
	imwrite("ThresholdTest.bmp", ThresholdTest);
    
    
	Mat CV_THRESH_BINARY = thresholdByCV(ThresholdTest, 128, 255, THRESH_BINARY);
	imageShow("CV_THRESH_BINARY", CV_THRESH_BINARY);
	imwrite("CV_THRESH_BINARY.bmp", CV_THRESH_BINARY);

	Mat CV_THRESH_BINARY_INV = thresholdByCV(ThresholdTest, 128, 255, THRESH_BINARY_INV);
	imageShow("CV_THRESH_BINARY_INV", CV_THRESH_BINARY_INV);
	imwrite("CV_THRESH_BINARY_INV.bmp", CV_THRESH_BINARY_INV);

	Mat CV_THRESH_TRUNC = thresholdByCV(ThresholdTest, 128, 255, THRESH_TRUNC);
	imageShow("CV_THRESH_TRUNC", CV_THRESH_TRUNC);
	imwrite("CV_THRESH_TRUNC.bmp", CV_THRESH_TRUNC);

	Mat CV_THRESH_TOZERO = thresholdByCV(ThresholdTest, 128, 255, THRESH_TOZERO);
	imageShow("CV_THRESH_TOZERO", CV_THRESH_TOZERO);
	imwrite("CV_THRESH_TOZERO.bmp", CV_THRESH_TOZERO);

	Mat CV_THRESH_TOZERO_INV = thresholdByCV(ThresholdTest, 128, 255, THRESH_TOZERO_INV);
	imageShow("CV_THRESH_TOZERO_INV", CV_THRESH_TOZERO_INV);
	imwrite("CV_THRESH_TOZERO_INV.bmp", CV_THRESH_TOZERO_INV);

	destroyAllWindows();

	return 0;
}

#ifdef OPENCV_H_
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
