#include "OpenCV.h"

using namespace std;
using namespace cv;

int main(void) {
    Mat roadBGR = imageRead(path + roadImage, IMREAD_COLOR);
    imageShow("roadBGR", roadBGR);

    Mat roadGray = convertColor(roadBGR, CV_BGR2GRAY);
    imageShow("roadGray", roadGray);

    Mat roadROI = trapezoidalROI(roadGray, 0.45, 0.6, 0.0, 1.0);
    imageShow("roadROI", roadROI);

    Mat roadCanny = cannyEdge(roadROI, 50, 100);
    imageShow("roadCanny", roadCanny);

    Mat roadSum = weightedSum(roadCanny, roadBGR);
    imageShow("roadSum", roadSum);

    destroyAllWindows();

	return 0;
}
