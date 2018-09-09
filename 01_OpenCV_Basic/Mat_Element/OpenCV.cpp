#include "OpenCV.h"

using namespace std;
using namespace cv;

int main(void) {
	string openPath = path + image;
	Mat lennaColor = imageRead(openPath, IMREAD_COLOR);
	imageShow("lennaColor", lennaColor);

	Mat lennaGray = imageRead(openPath, IMREAD_GRAYSCALE);
	imageShow("lennaGray", lennaGray);

	Mat ByAt_Gray = thresholdByAt(lennaGray, 128);
	imageShow("ByAt_Gray", ByAt_Gray);

	Mat ByAt_Color = thresholdByAt(lennaColor, 128);
	imageShow("ByAt_Color", ByAt_Color);

	Mat ByPtr_Gray = thresholdByPtr(lennaGray, 128);
	imageShow("ByPtr_Gray", ByPtr_Gray);

	Mat ByPtr_Color = thresholdByPtr(lennaColor, 128);
	imageShow("ByPtr_Color", ByPtr_Color);

	Mat ByData_Gray = thresholdByData(lennaGray, 128);
	imageShow("ByData_Gray", ByData_Gray);

	Mat ByData_Color = thresholdByData(lennaColor, 128);
	imageShow("ByData_Color", ByData_Color);

	destroyAllWindows();

	return 0;
}
