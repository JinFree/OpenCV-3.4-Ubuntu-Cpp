#include "OpenCV.h"

using namespace std;
using namespace cv;

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
