#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

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
    cout << "Display "<< imageName << " Channel: " << image.channels() << endl;
	namedWindow(imageName, flag);
    imshow(imageName, image);
	waitKey(0);
}
