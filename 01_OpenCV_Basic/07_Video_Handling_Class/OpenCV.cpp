#include "OpenCV.h"

using namespace std;
using namespace cv;

void videoProcessor::run() {
	Mat frameInput;
	Mat frameOutput;
	if(!isOpened())
		return;
	stop = false;
	while(!isStopped()){
		if(!readNextFrame(frameInput))
			break;
        if(videoNameInput.length() != 0)
            imshow(videoNameInput, frameInput);
        //image process
        frameInput.copyTo(frameOutput);
        frameOutput = convertColor(frameOutput);
        frameOutput = thresholdByCV(frameOutput);

        if(videoWritePath.length() != 0)
            writeNextFrame(frameOutput);
        if(videoNameOutput.length() != 0)
            imshow(videoNameOutput, frameOutput);
        frameNumber++;
        if(delay >= 0 && waitKey(delay) >= 0)
            stopIt();
        if(frameToStop >= 0 && getFrameNumber() == frameToStop)
            stopIt();
	}
}
int main(void) {
    videoProcessor processor;
    processor.setInput(videoPath+video);
    processor.setOutput(videoPath+"output.mp4");
    processor.showInput("Input");
    processor.showOutput("Output");
    //processor.stopAtFrameNumber(45);
    processor.setDelay(int(1000./processor.getFrameRate()));
    processor.run();
	return 0;
}
