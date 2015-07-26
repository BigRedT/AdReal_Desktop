#include "corner_detector.hpp"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

void testCorner() {
	Mat src, src_gray;
	Point center(300, 200), out;
	int searchRadius = 100;

	// Load source image and convert it to gray
	src = imread("resource/indoor.jpg", 1);
	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	// Detector
	CornerDetector detector;
	int t1, t2;
	t1 = getTickCount();
	detector.detectCorner(src_gray, center, searchRadius, out);
	t2 = getTickCount();

	//visualize
	circle(src, center, 3, Scalar(0, 255, 0), 2, 8, 0);
	circle(src, out, 3, Scalar(0), 2, 8, 0);

	namedWindow("Corners", WINDOW_AUTOSIZE);
	imshow("Corners", src);

	std::cout << "Timing:" << (t2 - t1) / getTickFrequency() << " seconds"
			<< std::endl;
	waitKey(0);
}

int main() {
	testCorner();
	return (0);
}


