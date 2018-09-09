#include "OpenCV.h"

using namespace std;
using namespace cv;

int main(void) {
    string openPath = path + image;
	Mat LennaBGR = imageRead(openPath, IMREAD_COLOR);
	imageShow("LennaBGR", LennaBGR, CV_WINDOW_NORMAL);
	saveChannels(path, "LennaBGR", "BGR", LennaBGR);

	cout << "CV_BGR2GRAY" << endl;
	Mat LennaGray = colorSpace("CV_BGR2GRAY", LennaBGR, CV_BGR2GRAY);
	imageShow("LennaGray", LennaGray, CV_WINDOW_NORMAL);
	saveChannels(path, "LennaGray", "", LennaGray);

	cout << "CV_BGR2HSV" << endl;
	Mat LennaHSV = colorSpace("CV_BGR2HSV", LennaBGR, CV_BGR2HSV);
	imageShow("LennaHSV", LennaHSV, CV_WINDOW_NORMAL);
	saveChannels(path, "LennaHSV", "HSV", LennaHSV);

	cout << "CV_BGR2YUV" << endl;
	Mat LennaYUV = colorSpace("CV_BGR2YUV", LennaBGR, CV_BGR2YUV);
	imageShow("LennaYUV", LennaYUV, CV_WINDOW_NORMAL);
	saveChannels(path, "LennaYUV", "YUV", LennaYUV);

	cout << "CV_BGR2Lab" << endl;
	Mat LennaLAB = colorSpace("CV_BGR2Lab", LennaBGR, CV_BGR2Lab);
	imageShow("LennaLAB", LennaLAB, CV_WINDOW_NORMAL);
	saveChannels(path, "LennaLAB", "LAB", LennaLAB);

	destroyAllWindows();

	return 0;
}
