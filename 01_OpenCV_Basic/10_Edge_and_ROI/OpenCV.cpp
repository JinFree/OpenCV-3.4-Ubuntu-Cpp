#include "OpenCV.h"

using namespace std;
using namespace cv;

int main(void) {
    Mat roadBGR = imageRead(path + roadImage, IMREAD_COLOR);
    imageShow("roadBGR", roadBGR);

    Mat roadGray = convertColor(roadBGR, CV_BGR2GRAY);
    imageShow("roadGray", roadGray);

    Mat roadROI = trapezoidalROI(roadGray, 0.4, 0.65, 0.0, 0.9);
    imageShow("roadROI", roadROI);

    Mat roadCanny = cannyEdge(roadROI, 50, 100);
    imageShow("roadCanny", roadCanny);

    Mat roadSum = weightedSum(roadCanny, roadBGR);
    imageShow("roadSum", roadSum);

    destroyAllWindows();

	return 0;
}
