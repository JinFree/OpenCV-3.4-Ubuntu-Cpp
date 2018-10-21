#include "OpenCV.h"

using namespace std;
using namespace cv;

string path = "../../Data/";
string lennaImage = "Lenna_Images/Lenna.png";
string roadImage = "Lane_Detection_Images/solidYellowLeft.jpg";

int main(void) {
	string openPath = path + lennaImage;

	Mat lennaColor = imageRead(openPath, IMREAD_COLOR);
	Mat lennaGray = imageRead(openPath, IMREAD_GRAYSCALE);
	Mat lennaOrigin = imageRead(openPath, IMREAD_UNCHANGED);

	imageShow("lennaOrigin, CV_WINDOW_NORMAL", lennaOrigin, CV_WINDOW_NORMAL);
	imageShow("lennaColor, CV_WINDOW_AUTOSIZE", lennaColor, CV_WINDOW_AUTOSIZE);
	imageShow("lennaGray, WINDOW_OPENGL", lennaGray, WINDOW_OPENGL);

	string savePath = path + "Lenna_Images/LennaGray.bmp";
	imwrite(savePath, lennaGray);
		
	string openPath2 = path + roadImage;
	Mat roadColor = imageRead(openPath2, IMREAD_COLOR);
	Mat roadGray = imageRead(openPath2, IMREAD_GRAYSCALE);
	Mat roadOrigin = imageRead(openPath2, IMREAD_UNCHANGED);
	Mat lennaGrayOrigin = imageRead(savePath, IMREAD_UNCHANGED);

	imageShow("roadOrigin, CV_WINDOW_FREERATIO", roadOrigin, CV_WINDOW_FREERATIO);
	imageShow("roadColor, CV_WINDOW_KEEPRATIO", roadColor, CV_WINDOW_KEEPRATIO);
	imageShow("roadGray, CV_GUI_NORMAL", roadGray, CV_GUI_NORMAL);
	imageShow("lennaGrayOrigin, CV_GUI_EXPANDED", lennaGrayOrigin, CV_GUI_EXPANDED);

	destroyAllWindows();

	return 0;
}

#ifdef OPENCV_H_
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
