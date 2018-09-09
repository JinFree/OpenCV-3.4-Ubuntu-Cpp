#include "OpenCV.h"

using namespace std;
using namespace cv;

int main(void) {
	string openPath = path + image;
	Mat lennaGray = imageRead(openPath, IMREAD_GRAYSCALE);
	imageShow("lennaGray", lennaGray);

	Mat ByAt = thresholdByAt(lennaGray, 128);
	imageShow("ByAt", ByAt);


	destroyAllWindows();

	return 0;
}
