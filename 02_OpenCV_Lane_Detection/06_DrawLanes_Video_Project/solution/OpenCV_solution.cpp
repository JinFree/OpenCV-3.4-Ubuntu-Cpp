#include "OpenCV.h"
#include "OpenCV_Video.h"

using namespace std;
using namespace cv;
Mat videoProcessing(Mat Input) {
    Mat output = Input.clone();
    Mat HSV = convertColor(output, CV_BGR2HSV);
    vector<Mat> HSV_HSV, HSV_Equalized;
    HSV_HSV = splitChannel(HSV);
    HSV_Equalized = splitChannel(HSV);
    HSV_Equalized[1] = histogramEqualize(HSV_Equalized[1]);
    HSV_Equalized[2] = histogramEqualize(HSV_Equalized[2]);
    Mat S_E_T_white = thresholdByCV(HSV_Equalized[1], 50, 255, THRESH_TOZERO_INV);
    Mat HSV_S_E_T_W = mergeChannel(HSV_HSV[0], S_E_T_white, HSV_Equalized[2]);
    Mat RGB_HSV_W = convertColor(HSV_S_E_T_W, CV_HSV2BGR);
    Mat W_gray = convertColor(RGB_HSV_W, CV_BGR2GRAY);
    Mat gray_th = thresholdByCV(W_gray, 240, 255, THRESH_BINARY);
    Mat roadROI2 = trapezoidalROI(gray_th, 0.35, 0.6, -0.1, 0.95);
    Mat roadCanny = cannyEdge(roadROI2, 50, 100);
    Mat roadROI = trapezoidalROI(roadCanny, 0.4, 0.65, 0.0, 0.9);
    vector<Vec4i> lines = HoughLinesP(roadROI, 1.0, CV_PI/60.0, 20, 10, 50);
    Mat roadLines = drawLanes(roadROI, lines);
    output = weightedSum(roadLines, output);
    return output;
}
Mat videoProcessor::videoProcess(Mat Input) {
    Mat output = Input.clone();
    output = videoProcessing(output);
    return output;
}
int main(void) {
    videoProcessor processor;
    processor.setInput(path+roadVideo);
    processor.setOutput(path+"Lane_Detection_Videos/draw_lane_project.mp4");
    processor.showInput("Input");
    processor.showOutput("Output");
    processor.setDelay(int(1000./processor.getFrameRate()));
    processor.run();
	return 0;
}
