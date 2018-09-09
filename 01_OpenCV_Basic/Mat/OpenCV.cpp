#include "OpenCV.h"

using namespace std;
using namespace cv;

int main(void) {
	Mat matrix1 = createMat(5,10,CV_8U, 50);
	imageShow("matrix1", matrix1);
	destroyAllWindows();

	return 0;
}
