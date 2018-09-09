#include "OpenCV.h"

using namespace std;
using namespace cv;

int main(void) {
	Mat matrix1(2,4,CV_8UC1, 50);
	imageShow("matrix1", matrix1);

	Mat matrix2(Size(4,2), CV_8UC1, Scalar(50));
	imageShow("matrix2", matrix2);

	matrix1.create(4,4,CV_8UC1);
	matrix1 = 100;
	imageShow("matrix1 after create", matrix1);

	Mat matrix3(4,4,CV_8UC3, Scalar(0,0,128));
	imageShow("matrix3", matrix3);

	Mat matrix4(Size(4,4),CV_8UC3);
	matrix4 = Scalar(0,0,128);
	imageShow("matrix4", matrix4);

	Mat matrix5(matrix1);
	// or matrix4 = matrix1;
	imageShow("matrix5 point matrix1", matrix5);

	matrix1 = 128;
	imageShow("matrix1 modified", matrix1);
	imageShow("matrix5 after modify matrix1", matrix5);

	Mat matrix6 = matrix3.clone();
	// or matrix2.copyTo(matrix5);
	imageShow("matrix6 cloned from matrix3", matrix6);

	matrix3 = Scalar(128,128,128);
	imageShow("matrix3 modified", matrix3);
	imageShow("matrix6 after modify matrix3", matrix6);

	destroyAllWindows();

	return 0;
}
