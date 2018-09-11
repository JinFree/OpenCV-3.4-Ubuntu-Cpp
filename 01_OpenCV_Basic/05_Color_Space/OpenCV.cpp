#include "OpenCV.h"

using namespace std;
using namespace cv;

int main(void) {
    string openPath = path + lennaImage;
    string writePath = path +  "Lenna_Images/";
	Mat LennaBGR = imageRead(openPath, IMREAD_COLOR);
	imageShow("LennaBGR", LennaBGR);
	saveChannels(writePath, "LennaBGR", "BGR", LennaBGR);

	Mat LennaGray = convertColor(LennaBGR, CV_BGR2GRAY);
	imageShow("LennaGray", LennaGray);
    showChannels("LennaGray", LennaGray);
	saveChannels(writePath, "LennaGray", "", LennaGray);

	Mat LennaHSV = convertColor(LennaBGR, CV_BGR2HSV);
	imageShow("LennaHSV", LennaHSV);
    showChannels("LennaHSV", LennaHSV);
	saveChannels(writePath, "LennaHSV", "HSV", LennaHSV);

	Mat LennaYUV = convertColor(LennaBGR, CV_BGR2YUV);
	imageShow("LennaYUV", LennaYUV);
    showChannels("LennaYUV", LennaYUV);
	saveChannels(writePath, "LennaYUV", "YUV", LennaYUV);

	Mat LennaLAB = convertColor(LennaBGR, CV_BGR2Lab);
	imageShow("LennaLAB", LennaLAB);
    showChannels("LennaLAB", LennaLAB);
	saveChannels(writePath, "LennaLAB", "LAB", LennaLAB);

	destroyAllWindows();

	return 0;
}
