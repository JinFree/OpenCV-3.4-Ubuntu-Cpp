#include "OpenCV.h"

using namespace std;
using namespace cv;

string path = "../../Data/";
string image = "Lenna.png";

int main(void) {
	string openPath = path + image;

	Mat lennaColor = imageRead(openPath, IMREAD_COLOR);
	Mat lennaGray = imageRead(openPath, IMREAD_GRAYSCALE);
	Mat lennaOrigin = imageRead(openPath, IMREAD_UNCHANGED);

	imageShow("lennaOrigin, CV_WINDOW_NORMAL", lennaOrigin, CV_WINDOW_NORMAL );
	imageShow("lennaColor, CV_WINDOW_AUTOSIZE", lennaColor, CV_WINDOW_AUTOSIZE);
	imageShow("lennaGray, WINDOW_OPENGL", lennaGray, WINDOW_OPENGL  );

	string savePath = path + "LennaGray.bmp";
	imwrite(savePath, lennaGray);

	Mat lennaColor2 = imageRead(savePath, CV_LOAD_IMAGE_COLOR);
	Mat lennaGray2 = imageRead(savePath, CV_LOAD_IMAGE_GRAYSCALE);
	Mat lennaOrigin2 = imageRead(savePath, CV_LOAD_IMAGE_UNCHANGED);

	imageShow("lennaOrigin2, CV_WINDOW_FREERATIO", lennaOrigin2, CV_WINDOW_FREERATIO);
	imageShow("lennaGray2, CV_WINDOW_KEEPRATIO", lennaGray2, CV_WINDOW_KEEPRATIO);
	imageShow("lennaColor2, CV_GUI_NORMAL", lennaColor2, CV_GUI_NORMAL );
	imageShow("lennaColor2, CV_GUI_EXPANDED", lennaColor2, CV_GUI_EXPANDED );

	destroyAllWindows();

	return 0;
}
