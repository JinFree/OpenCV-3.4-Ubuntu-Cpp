#include "OpenCV.h"

using namespace std;
using namespace cv;

int main(void) {
    Mat LennaGray = imageRead(path + lennaImage, IMREAD_GRAYSCALE);
    imageShow("LennaGray", LennaGray);

    // equalizeHist -> histogramEqualize
    Mat LennaHistogram = histogramEqualize(LennaGray);
    imageShow("LennaHistogram",LennaHistogram);

    // CLAHE -> clippedHistogramEqualize
    Mat LennaCLAHE = clippedHistogramEqualize(LennaGray, 40.0);
    imageShow("LennaCLAHE", LennaCLAHE);

	destroyAllWindows();

    Mat roadBGR = imageRead(path + roadImage, IMREAD_COLOR);
    imageShow("roadBGR", roadBGR);
    vector<Mat> BGR;
    BGR = splitChannel(roadBGR);
    int i;
    for ( i = 0 ; i < 3 ; i++ ) {
        BGR[i] = histogramEqualize(BGR[i]);
    }
    Mat roadBGR2 = mergeChannel(BGR);
    imageShow("roadBGR2", roadBGR2);

    Mat roadHSV = convertColor(roadBGR, CV_BGR2HSV);
    vector<Mat> HSV_HSV, HSV_Equalized;
    HSV_HSV = splitChannel(roadHSV);
    HSV_Equalized = splitChannel(roadHSV);
    for ( i = 0 ; i < 3 ; i++ ) {
        HSV_Equalized[i] = histogramEqualize(HSV_Equalized[i]);
    }

    Mat roadHSV_HSV = mergeChannel(HSV_Equalized);
    roadHSV_HSV = convertColor(roadHSV_HSV, CV_HSV2BGR);
    imageShow("roadHSV_HSV", roadHSV_HSV);

    Mat roadHSV_H = mergeChannel(HSV_Equalized[0], HSV_HSV[1], HSV_HSV[2]);
    roadHSV_H = convertColor(roadHSV_H, CV_HSV2BGR);
    imageShow("roadHSV_H", roadHSV_H);

    Mat roadHSV_S= mergeChannel(HSV_HSV[0], HSV_Equalized[1], HSV_HSV[2]);
    roadHSV_S = convertColor(roadHSV_S, CV_HSV2BGR);
    imageShow("roadHSV_S", roadHSV_S);

    Mat roadHSV_V = mergeChannel(HSV_HSV[0], HSV_HSV[1], HSV_Equalized[2]);
    roadHSV_V = convertColor(roadHSV_V, CV_HSV2BGR);
    imageShow("roadHSV_V", roadHSV_V);

    Mat roadHSV_SV = mergeChannel(HSV_HSV[0], HSV_Equalized[1], HSV_Equalized[2]);
    roadHSV_SV = convertColor(roadHSV_SV, CV_HSV2BGR);
    imageShow("roadHSV_SV", roadHSV_SV);

    destroyAllWindows();

	return 0;
}
