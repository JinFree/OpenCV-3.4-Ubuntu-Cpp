#include <iostream>
#include <iomanip>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

string path = "../../Data/Lenna_Images/";
string image = "Lenna.png";
string videoPath = "../../Data/Lane_Detection_Videos/";
string video = "test.mp4";
class videoProcessor {
public:
	bool setInput(string videoPath);
	bool setOutput(string videoPath, int codec = 0, double framerate = 0.0, bool isColor = true);
	void showInput(string windowName);
	void showOutput(string windowName);
	double getFrameRate();
	Size getFrameSize();
	void stopIt();
	bool isStopped();
	bool isOpened();
	void setDelay(int d);
	bool readNextFrame(Mat& frame);
	void writeNextFrame(Mat& frame);
	long getFrameNumber();
	void run();
	void stopAtFrameNumber(long frame);
	int getCodec(char codec[4]);
private:
	VideoCapture capture;
	string videoReadPath;
	string videoNameInput;
	string videoNameOutput;
	int delay;
	long frameNumber;
	long frameToStop;
	bool stop;
	VideoWriter writer;
	string videoWritePath;
	int currentIndex;
	int digits;
	string extension;
	double frameRate;
	Size frameSize;
};
bool videoProcessor::setInput(string videoPath) {
	videoReadPath = videoPath;
	frameNumber = 0;
	capture.release();
	return capture.open(videoReadPath);
}
bool videoProcessor::setOutput(string videoPath, int codec, double framerate, bool isColor) {
	videoWritePath = videoPath;
	extension.clear();
	if(framerate == 0.0) {
		framerate = getFrameRate();
	}
	char c[4];
	if(codec == 0) {
		codec = getCodec(c);
	}
	return writer.open(videoWritePath, codec, framerate, getFrameSize(), isColor);
}
void videoProcessor::showInput(string windowName) {
	videoNameInput = windowName;
	namedWindow(videoNameInput, CV_WINDOW_NORMAL);
}
void videoProcessor::showOutput(string windowName) {
	videoNameOutput = windowName;
	namedWindow(videoNameOutput, CV_WINDOW_NORMAL);
}
double videoProcessor::getFrameRate() {
	return frameRate = capture.get(CV_CAP_PROP_FPS);
}
Size videoProcessor::getFrameSize() {
	return frameSize = Size((int)capture.get(CAP_PROP_FRAME_WIDTH),
        (int)capture.get(CAP_PROP_FRAME_HEIGHT));
}
void videoProcessor::stopIt() {
	stop = true;
}
bool videoProcessor::isStopped() {
	return stop;
}
bool videoProcessor::isOpened() {
	return capture.isOpened();
}
void videoProcessor::setDelay(int d) {
	delay = d;
}
bool videoProcessor::readNextFrame(Mat& frame) {
	return capture.read(frame);
}
void videoProcessor::writeNextFrame(Mat& frame) {
	if(extension.length()) {
		stringstream stream;
		stream << videoWritePath << setfill('0') << setw(digits)
		<< currentIndex++ << extension;
	imwrite(stream.str(), frame);
	}
	else {
		writer.write(frame);
	}
}
long videoProcessor::getFrameNumber() {
	long frameNumber = static_cast<long>(capture.get(CV_CAP_PROP_POS_FRAMES));
	return frameNumber;
}
void videoProcessor::stopAtFrameNumber(long frame) {
	frameToStop = frame;
}
int videoProcessor::getCodec(char codec[4]) {
	union {
		int value;
		char code[4];
	} returned;
	returned.value = static_cast<int>(capture.get(CV_CAP_PROP_FOURCC));
	int i;
	for( i = 0 ; i < 4 ; i++ ) {
		codec[i] = returned.code[i];
	}
	return returned.value;
}


Mat mergeChannel(vector<Mat> channels);
vector<Mat> splitChannel(Mat image);
Mat convertColor(Mat image, int flag = CV_BGR2GRAY);
void showChannels(string imageName, Mat image);
void saveChannels(string path, string ImageName, string channelname, Mat image);
Mat adaptiveThresholdByCV(Mat image, double maxValue = 255, int adaptiveMethod = ADAPTIVE_THRESH_GAUSSIAN_C, int thresholdType = THRESH_BINARY, int blockSize = 3, double C = 0);
Mat thresholdByCV(Mat image, double thresh = 128, double maxval = 255, int type = THRESH_BINARY);
Mat thresholdByAt(Mat image, uchar thresh = 128);
Mat thresholdByPtr(Mat image, uchar thresh = 128);
Mat thresholdByData(Mat image, uchar thresh = 128);
Mat imageRead(string openPath, int flag = IMREAD_UNCHANGED);
void imageShow(string imageName, Mat image, int flag = CV_WINDOW_NORMAL);

Mat mergeChannel(vector<Mat> channels) {
	Mat result;
	merge(channels,result);
	return result;
}
vector<Mat> splitChannel(Mat image) {
	vector<Mat> channels;
	split(image, channels);
	return channels;
}
Mat convertColor(Mat image, int flag) {
	Mat result;
	cvtColor(image, result, flag);
	return result;
}
void showChannels(string imageName, Mat image) {
	if(image.channels() != 1) {
		vector<Mat> channels;
		channels = splitChannel(image);
		imageShow(imageName+"_0", channels[0]);
		imageShow(imageName+"_1", channels[1]);
		imageShow(imageName+"_2", channels[2]);
	}
	else if(image.channels() == 1){
		imageShow("GrayScale", image);
	}
	return;
}
void saveChannels(string path, string ImageName, string channelname, Mat image) {
	if(image.channels() != 1) {
		vector<Mat> channels;
		channels = splitChannel(image);
		int i;
		for( i = 0 ; i < 3 ; i++) {
			imwrite(path+ImageName+"_"+channelname[i]+".bmp", channels[i]);
		}
	}
	else {
		imwrite(path+ImageName+".bmp", image);
	}
	return;
}
Mat adaptiveThresholdByCV(Mat image, double maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C ) {
	Mat result;
	adaptiveThreshold(image, result, maxValue, adaptiveMethod, thresholdType, blockSize, C);
	return result;
}
Mat thresholdByCV(Mat image, double thresh, double maxval, int type) {
	Mat result;
	threshold(image, result, thresh, maxval, type);
	return result;
}
Mat thresholdByAt(Mat image, uchar thresh) {
	int i,j;
	Mat result = image.clone();
	if(result.type() == CV_8UC1) {
		for( j = 0 ; j < result.rows ; j++) {
			for ( i = 0 ; i < result.cols ; i++ ) {
				uchar value = result.at<uchar>(j,i);
				value = value > thresh ? 255 : 0;
				result.at<uchar>(j,i) = value;
			}
		}
	}
	else if(result.type() == CV_8UC3) {
		for( j = 0 ; j < result.rows ; j++) {
			for ( i = 0 ; i < result.cols ; i++ ) {
				Vec3b value = result.at<Vec3b>(j, i);
				int c;
				for(c = 0 ; c < 3 ; c++) {
					value[c] = value[c] > thresh ? 255 : 0;
				}
				result.at<Vec3b>(j,i) = value;
			}
		}
	}
	return result;
}
Mat thresholdByPtr(Mat image, uchar thresh) {
	int i,j;
	Mat result = image.clone();
	if(result.type() == CV_8UC1) {
		for( j = 0 ; j < result.rows ; j++) {
			uchar* image_pointer = result.ptr<uchar>(j);
			for ( i = 0 ; i < result.cols ; i++ ) {
				uchar value = image_pointer[i];
				value = value > thresh ? 255 : 0;
				image_pointer[i] = value;
			}
		}
	}
	else if(result.type() == CV_8UC3) {
		for( j = 0 ; j < result.rows ; j++) {
			uchar* image_pointer = result.ptr<uchar>(j);
			for ( i = 0 ; i < result.cols ; i++ ) {
				int c;
				for(c = 0 ; c < 3 ; c++) {
					uchar value = image_pointer[i*3+c];
					value = value > thresh ? 255 : 0;
					image_pointer[i*3+c] = value;
				}
			}
		}
	}
	return result;
}
Mat thresholdByData(Mat image, uchar thresh) {
	int i,j;
	Mat result = image.clone();
	uchar *image_data = result.data;
	if(result.type() == CV_8UC1) {
		for( j = 0 ; j < result.rows ; j++) {
			for ( i = 0 ; i < result.cols ; i++ ) {
				uchar value = image_data[j * result.cols + i];
				value = value > thresh ? 255 : 0;
				image_data[j * result.cols + i] = value;
			}
		}
	}
	else if(result.type() == CV_8UC3) {
		for( j = 0 ; j < result.rows ; j++) {
			for ( i = 0 ; i < result.cols ; i++ ) {
				int c;
				for(c = 0 ; c < 3 ; c++) {
					uchar value = image_data[(j * result.cols + i) * 3 + c];
					value = value > thresh ? 255 : 0;
					image_data[(j * result.cols + i) * 3 + c] = value;
				}
			}
		}
	}
	return result;
}
Mat imageRead(string openPath, int flag) {
	Mat image = imread(openPath, flag);
	if(image.empty()) {
		cout<<"Image Not Opened"<<endl;
		cout<<"Program Abort"<<endl;
		exit(1);
	}
	else {
		cout<<"Image Opened"<<endl;
		return image;
	}
}
void imageShow(string imageName, Mat image, int flag) {
	namedWindow(imageName, flag);
	cout << "Display "<< imageName << " Channel: " << image.channels() << endl;
    imshow(imageName, image);
	waitKey(0);
}
