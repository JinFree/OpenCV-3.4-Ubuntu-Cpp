#include "OpenCV.h"

using namespace std;
using namespace cv;

string path = "../../Data/";
string lennaImage = "Lenna_Images/Lenna.png";
string roadImage = "Lane_Detection_Images/solidYellowLeft.jpg";

int main(void) {
	double timer;
	string openPath = path + lennaImage;
	Mat lennaColor = imageRead(openPath, IMREAD_COLOR);
	imageShow("lennaColor", lennaColor);

	Mat lennaGray = imageRead(openPath, IMREAD_GRAYSCALE);
	imageShow("lennaGray", lennaGray);

	timer = (double)getTickCount();
	Mat ByAt_Gray = thresholdByAt(lennaGray, 128);
	timer = ((double)getTickCount() - timer) / getTickFrequency();
	cout << "threshold gray time at =  " << timer << " sec" << endl;
	imageShow("ByAt_Gray", ByAt_Gray);

	timer = (double)getTickCount();
	Mat ByPtr_Gray = thresholdByPtr(lennaGray, 128);
	timer = ((double)getTickCount() - timer) / getTickFrequency();
	cout << "threshold gray time ptr =  " << timer << " sec" << endl;
	imageShow("ByPtr_Gray", ByPtr_Gray);

	timer = (double)getTickCount();
	Mat ByData_Gray = thresholdByData(lennaGray, 128);
	timer = ((double)getTickCount() - timer) / getTickFrequency();
	cout << "threshold gray time data =  " << timer << " sec" << endl;
	imageShow("ByData_Gray", ByData_Gray);

	timer = (double)getTickCount();
	Mat ByAt_Color = thresholdByAt(lennaColor, 128);
	timer = ((double)getTickCount() - timer) / getTickFrequency();
	cout << "threshold color time at =  " << timer << " sec" << endl;
	imageShow("ByAt_Color", ByAt_Color);

	timer = (double)getTickCount();
	Mat ByPtr_Color = thresholdByPtr(lennaColor, 128);
	timer = ((double)getTickCount() - timer) / getTickFrequency();
	cout << "threshold color time ptr =  " << timer << " sec" << endl;
	imageShow("ByPtr_Color", ByPtr_Color);

	timer = (double)getTickCount();
	Mat ByData_Color = thresholdByData(lennaColor, 128);
	timer = ((double)getTickCount() - timer) / getTickFrequency();
	cout << "threshold color time data =  " << timer << " sec" << endl;
	imageShow("ByData_Color", ByData_Color);

	destroyAllWindows();

	return 0;
}

#ifdef OPENCV_H_
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
