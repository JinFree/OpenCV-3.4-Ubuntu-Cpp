#include "OpenCV.h"

using namespace std;
using namespace cv;

int main(void) {
    string openPath = video;
    VideoCapture capture(video);
    if(!capture.isOpened()) {
        return 1;
    }
    double rate = capture.get(CV_CAP_PROP_FPS);
    bool stop(false);
    Mat frame;
    namedWindow("Extracted Frame", CV_WINDOW_NORMAL);
    int delay = 1000/rate;

    while(!stop) {
        if(!capture.read(frame)) {
            break;
        }
        imshow("Extracted Frame", frame);
        if(waitKey(delay) >= 0) {
            stop = true;
        }
    }
    capture.release();

	destroyAllWindows();

	return 0;
}
