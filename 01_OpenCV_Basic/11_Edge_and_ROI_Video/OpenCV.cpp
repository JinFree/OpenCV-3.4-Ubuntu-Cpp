#include "OpenCV.h"
#include "OpenCV_Video.h"

using namespace std;
using namespace cv;

Mat videoProcessor::videoProcess(Mat Input) {
    Mat output = Input.clone();
    output = convertColor(output, CV_BGR2GRAY);
    output = trapezoidalROI(output, 0.35, 0.6, -0.1, 0.95);
    output = cannyEdge(output, 50,100);
    output = trapezoidalROI(output, 0.4, 0.65, 0.0, 0.9);
    output = weightedSum(output, Input);
    return output;
}
int main(void) {
    videoProcessor processor;
    processor.setInput(path+roadVideo);
    processor.setOutput(path+"Lane_Detection_Videos/find_lane_test.mp4");
    processor.showInput("Input");
    processor.showOutput("Output");
    processor.setDelay(int(1000./processor.getFrameRate()));
    processor.run();
	return 0;
}
