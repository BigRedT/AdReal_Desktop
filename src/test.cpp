#include "corner_detector.hpp"
#include "misc.hpp"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

void testCorner() {
	Mat src, src_gray;
	Point2f center(300, 200), out;
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

void testRect() {
	Mat src, src_gray;

	// Load source image and convert it to gray
	src = imread("resource/s1.png", 1);
	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	// detect rectangles
	std::vector<quad> quads;
	findRectangles(src_gray, quads);
	std::cout << quads.size() << std::endl;

	// create array of array of points
	cv::Point **quadPts = new cv::Point* [quads.size()];
	int *npts = new int [quads.size()];
	for(int i=0; i<(int)quads.size(); i++) {
		npts[i] = 4;
		quadPts[i] = new cv::Point [4];
		for(int j=0; j<4; j++) {
			quadPts[i][j] = quads[i].points[j];
		}
	}

	//const int npts_[] = {npts};
	//const cv::Point2f *pts[] = {quadPts};

	// draw quads;
	cv::polylines(src, quadPts, npts, quads.size(), true, Scalar(0,255,0), 3, LINE_AA);

	// show
	namedWindow("Rectangle", WINDOW_AUTOSIZE);
	imshow("Rectangle", src);
	waitKey(0);

}

