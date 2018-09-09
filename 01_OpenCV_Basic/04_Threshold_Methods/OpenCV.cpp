#include "OpenCV.h"

using namespace std;
using namespace cv;

int main(void) {
	double timer;
	string openPath = path + image;
	Mat lennaColor = imageRead(openPath, IMREAD_COLOR);
	imageShow("lennaColor", lennaColor);

	Mat lennaGray = imageRead(openPath, IMREAD_GRAYSCALE);
	imageShow("lennaGray", lennaGray);

	timer = (double)getTickCount();
	Mat ByPtr_Gray = thresholdByPtr(lennaGray, 128);
	timer = ((double)getTickCount() - timer) / getTickFrequency();
	cout << "threshold gray time ptr =  " << timer << " sec" << endl;
	imageShow("ByPtr_Gray", ByPtr_Gray);

	timer = (double)getTickCount();
	Mat ByPtr_Color = thresholdByPtr(lennaColor, 128);
	timer = ((double)getTickCount() - timer) / getTickFrequency();
	cout << "threshold color time ptr =  " << timer << " sec" << endl;
	imageShow("ByPtr_Color", ByPtr_Color);

	

	destroyAllWindows();

	return 0;
}
