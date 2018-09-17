#include "OpenCV.h"

using namespace std;
using namespace cv;

int main(void) {
    Mat roadBGR = imageRead(path + roadImage, IMREAD_COLOR);
    imageShow("roadBGR", roadBGR);

    Mat roadGray = convertColor(roadBGR, CV_BGR2GRAY);
    //imageShow("roadGray", roadGray);

    Mat roadROI2 = trapezoidalROI(roadGray, 0.35, 0.6, -0.1, 0.95);
    //imageShow("roadROI2", roadROI2);

    Mat roadCanny = cannyEdge(roadROI2, 50, 100);
    //imageShow("roadCanny", roadCanny);

    Mat roadROI = trapezoidalROI(roadCanny, 0.4, 0.65, 0.0, 0.9);
    //imageShow("roadROI", roadROI);

    vector<Vec4i> lines = HoughLinesP(roadROI, 1.0, CV_PI/60.0, 20, 10, 50);
    Mat roadLines = drawLanes(roadROI, lines);

    Mat roadSum = weightedSum(roadLines, roadBGR);
    imageShow("roadSum", roadSum);

    destroyAllWindows();

	return 0;
}
