#include "OpenCV.h"

using namespace std;
using namespace cv;

int main(void) {
	Mat LennaGray = imageRead(path + lennaImage, IMREAD_GRAYSCALE);
	imageShow("LennaGray", LennaGray);

	Mat LennaGrayNoise = addSaltAndPepper(LennaGray, 0.01);
	imageShow("LennaGrayNoise", LennaGrayNoise);

	Mat LennaMeanBlur = meanBlur(LennaGrayNoise, Size(5,5));
	imageShow("LennaMeanBlur", LennaMeanBlur);

	Mat LennaGaussianBlur = gaussianBlur(LennaGrayNoise, Size(5,5), 2);
	imageShow("LennaGaussianBlur", LennaGaussianBlur);

	Mat LennaMedianBlur = medianBlur(LennaGrayNoise, 5);
	imageShow("LennaMedianBlur", LennaMedianBlur);

	Mat LennaBilateral = bilateralFilter(LennaGrayNoise, 5, 10.0, 10.0);
	imageShow("LennaBilateral", LennaBilateral);

	destroyAllWindows();

	Mat RoadGray = imageRead(path+roadImage, IMREAD_UNCHANGED);
	imageShow("RoadGray", RoadGray);

	Mat RoadMeanBlur = meanBlur(RoadGray, Size(5,5));
	imageShow("RoadMeanBlur", RoadMeanBlur);

	Mat RoadGaussianBlur = gaussianBlur(RoadGray, Size(5,5), 2);
	imageShow("RoadGaussianBlur", RoadGaussianBlur);

	Mat RoadMedianBlur = medianBlur(RoadGray, 5);
	imageShow("RoadMedianBlur", RoadMedianBlur);

	Mat RoadBilateral = bilateralFilter(RoadGray, 5, 10.0, 10.0);
	imageShow("RoadBilateral", RoadBilateral);

	destroyAllWindows();

	return 0;
}
