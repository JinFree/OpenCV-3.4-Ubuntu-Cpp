#include "OpenCV.h"

using namespace std;
using namespace cv;

int main(void) {
    string openPath = path + image;
	Mat LennaBGR = imageRead(openPath, IMREAD_COLOR);
	imageShow("LennaBGR", LennaBGR);
	saveChannels(path, "LennaBGR", "BGR", LennaBGR);

	Mat LennaGray = convertColor(LennaBGR, CV_BGR2GRAY);
	imageShow("LennaGray", LennaGray);
    showChannels("LennaGray", LennaGray);
	saveChannels(path, "LennaGray", "", LennaGray);

	Mat LennaHSV = convertColor(LennaBGR, CV_BGR2HSV);
	imageShow("LennaHSV", LennaHSV);
    showChannels("LennaHSV", LennaHSV);
	saveChannels(path, "LennaHSV", "HSV", LennaHSV);

	Mat LennaYUV = convertColor(LennaBGR, CV_BGR2YUV);
	imageShow("LennaYUV", LennaYUV);
    showChannels("LennaYUV", LennaYUV);
	saveChannels(path, "LennaYUV", "YUV", LennaYUV);

	Mat LennaLAB = convertColor(LennaBGR, CV_BGR2Lab);
	imageShow("LennaLAB", LennaLAB);
    showChannels("LennaLAB", LennaLAB);
	saveChannels(path, "LennaLAB", "LAB", LennaLAB);

	destroyAllWindows();

	return 0;
}
