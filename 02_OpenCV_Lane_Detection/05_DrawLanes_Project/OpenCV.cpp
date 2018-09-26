#include "OpenCV.h"

using namespace std;
using namespace cv;
Mat videoProcessing(Mat Input) {
    Mat output = Input.clone();
    Mat roadGray = convertColor(output, CV_BGR2GRAY);
    Mat roadROI2 = trapezoidalROI(roadGray, 0.35, 0.6, -0.1, 0.95);
    Mat roadCanny = cannyEdge(roadROI2, 50, 100);
    Mat roadROI = trapezoidalROI(roadCanny, 0.4, 0.65, 0.0, 0.9);
    vector<Vec4i> lines = HoughLinesP(roadROI, 1.0, CV_PI/60.0, 20, 10, 50);
    Mat roadLines = drawLanes(roadROI, lines);
    output = weightedSum(roadLines, output);
    return output;
}
int main(void) {
    string roadImagePath = "../../Data/Lane_Detection_Images/";
    string file1 = "solidYellowCurve2.jpg";
    string file2 = "solidWhiteRight.jpg";
    string file3 = "solidYellowCurve.jpg";
    string file4 = "solidWhiteCurve.jpg";
    string file5 = "solidYellowLeft.jpg";
    string file6 = "whiteCarLaneSwitch.jpg";
    string file7 = "test.jpg";

    Mat roadBGR1 = imageRead(roadImagePath + file1, IMREAD_COLOR);
    imageShow("roadBGR1", roadBGR1);

    Mat Output1 =  videoProcessing(roadBGR1);
    imageShow("Output1", Output1);

    Mat roadBGR2 = imageRead(roadImagePath + file2, IMREAD_COLOR);
    imageShow("roadBGR2", roadBGR2);

    Mat Output2 =  videoProcessing(roadBGR2);
    imageShow("Output2", Output2);

    Mat roadBGR3 = imageRead(roadImagePath + file3, IMREAD_COLOR);
    imageShow("roadBGR3", roadBGR3);

    Mat Output3 =  videoProcessing(roadBGR3);
    imageShow("Output3", Output3);

    Mat roadBGR4 = imageRead(roadImagePath + file4, IMREAD_COLOR);
    imageShow("roadBGR4", roadBGR4);

    Mat Output4 =  videoProcessing(roadBGR4);
    imageShow("Output4", Output4);

    Mat roadBGR5 = imageRead(roadImagePath + file5, IMREAD_COLOR);
    imageShow("roadBGR5", roadBGR5);

    Mat Output5 =  videoProcessing(roadBGR5);
    imageShow("Output5", Output5);

    Mat roadBGR6 = imageRead(roadImagePath + file6, IMREAD_COLOR);
    imageShow("roadBGR6", roadBGR6);

    Mat Output6 =  videoProcessing(roadBGR6);
    imageShow("Output6", Output6);

    Mat roadBGR7 = imageRead(roadImagePath + file7, IMREAD_COLOR);
    imageShow("roadBGR7", roadBGR7);

    Mat Output7 =  videoProcessing(roadBGR7);
    imageShow("Output7", Output7);

    destroyAllWindows();

	return 0;
}
