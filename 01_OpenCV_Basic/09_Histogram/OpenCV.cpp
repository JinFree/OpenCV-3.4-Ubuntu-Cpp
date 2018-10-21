#include "OpenCV.h"

using namespace std;
using namespace cv;

string path = "../../Data/";
string lennaImage = "Lenna_Images/Lenna.png";
string roadImage = "Lane_Detection_Images/solidYellowLeft.jpg";
string sudokuImage = "sudoku-original.jpg";
string roadVideo = "Lane_Detection_Videos/solidWhiteRight.mp4";

int main(void) {
    Mat LennaGray = imageRead(path + lennaImage, IMREAD_GRAYSCALE);
    imageShow("LennaGray", LennaGray);

    Mat LennaHistogram = histogramEqualize(LennaGray);
    imageShow("LennaHistogram",LennaHistogram);

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

#ifdef OPENCV_H_
Mat clippedHistogramEqualize(Mat image, double clipLimit, Size tileGridSize) {
	Mat result;
	cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
	clahe->setClipLimit(clipLimit);
	clahe->setTilesGridSize(tileGridSize);
	clahe->apply(image, result);
	return result;
}
Mat histogramEqualize(Mat image) {
	Mat result;
	equalizeHist(image, result);
	return result;
}
Mat bilateralFilter(Mat image, int d, double sigmaColor, double sigmaSpace, int borderType) {
	Mat result;
	bilateralFilter(image, result, d, sigmaColor, sigmaSpace, borderType);
	return result;
}
Mat medianBlur(Mat image, int kernelSize) {
	Mat result;
	medianBlur(image, result, kernelSize);
	return result;
}
Mat gaussianBlur(Mat image, Size kernelSize, double sigmaX, double sigmaY, int borderType) {
	Mat result;
	GaussianBlur(image, result, kernelSize, sigmaX, sigmaY, borderType);
	return result;
}
Mat meanBlur(Mat image, Size kernelSize, Point anchor, int borderType) {
	Mat result;
	blur(image, result, kernelSize, anchor, borderType);
	return result;
}
Mat addSaltAndPepper(Mat image, double noiseRatio) {
	Mat result = image.clone();
	int i;
	int rows = result.rows;
	int cols = result.cols;
	int ch = result.channels();
	int num_of_noise_pixels = (int)((double)(rows*cols*ch)*noiseRatio);
	for ( i = 0 ; i < num_of_noise_pixels ; i++ ){
		int r = rand() % rows;
		int c = rand() % cols;
		int _ch = rand() % ch;

		uchar* pixel = result.ptr<uchar>(r)+(c*ch)+_ch;
		*pixel = (rand()%2==1)?255:0;
	}
	return result;
}
Mat mergeChannel(Mat ch1, Mat ch2, Mat ch3) {
	Mat result;
	vector<Mat> channels;
	channels.push_back(ch1);
	channels.push_back(ch2);
	channels.push_back(ch3);
	merge(channels, result);
	return result;
}
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
#endif

#ifdef OPENCV_VIDEO_H_
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

        frameOutput = videoProcess(frameInput);

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
#endif
