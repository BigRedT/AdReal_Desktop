#include "test.hpp"
#include "corner_detector.hpp"
#include "tracker.hpp"
#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video/tracking.hpp>

using namespace cv;
using std::vector;

int main() {
	const std::string video_filename = "resource/video_simple.mp4";
	// read video
	cv::VideoCapture capture(video_filename);
	if (!capture.isOpened()) {
		std::cout << "Video file could not be opened" << std::endl;
		return -1;
	}

	// Create window to display video frames
	cv::namedWindow("AdReal", WINDOW_NORMAL);

	// detector
	CornerDetector detector;
	// tracker
	Tracker tracker;

	// kalman filter
	KalmanFilter KF(8, 8, 8);  //numState, numMeasure, numControl
	setIdentity(KF.measurementMatrix);
	setIdentity(KF.transitionMatrix);
	setIdentity(KF.controlMatrix);
	KF.processNoiseCov = Mat::eye(8, 8, CV_32F) * 0.001;
	KF.measurementNoiseCov = Mat::eye(8, 8, CV_32F) * 0.00001;

	Mat delta(8, 1, CV_32F);
	Mat measure(8, 1, CV_32F);

	// points
	vector<Point> inPts;
	vector<Point> outPts;
	vector<uchar> status;

	// init tracking point
	inPts.push_back(Point(1016,166));
	inPts.push_back(Point(1480,158));
	inPts.push_back(Point(1470,796));
	inPts.push_back(Point(986,774));

	// Process each video frame
	Mat frame_c, frame, preFrame_c, preFrame;
	capture >> preFrame_c;
	cvtColor(preFrame_c, preFrame, COLOR_BGR2GRAY);

	int count = 0;
	while (1) {
		capture >> frame_c;
		if (frame_c.empty()) {
			std::cout << "Finished processing the video" << std::endl;
			break;
		}
		cvtColor(frame_c, frame, COLOR_BGR2GRAY);

		if (count < 50) {
			// run tracker
			tracker.trackPoints(preFrame, inPts, frame, outPts, status);
			for (int i = 0; i < (int)(inPts.size()); i++) {
				delta.at<float>(i * 2, 0) = outPts[i].x - inPts[i].x;
				delta.at<float>(i * 2 + 1, 0) = outPts[i].y - inPts[i].y;
			}

			// kalman predict
			KF.predict(delta);
			KF.statePost = KF.statePre;

		} else {
			// run detector
			for (int i=0; i < (int)(inPts.size()); i++) {
				detector.detectCorner(frame,inPts[i], 50, outPts[i]);
				measure.at<float>(i*2, 0) = outPts[i].x;
				measure.at<float>(i*2+1,0) = outPts[i].y;
			}

			// kalman corrector
			KF.correct(measure);
			count = 0;
		}

		// update the inpts
		for (int i = 0; i <(int)(inPts.size()); i++) {
			inPts[i].x = KF.statePost.at<float>(i * 2, 0);
			inPts[i].y = KF.statePost.at<float>(i * 2 + 1, 0);
		}

		// visualize the point
		for (int i = 0; i <(int)(inPts.size()); i++) {
			circle(frame, inPts[i], 3, Scalar(0, 255, 0), 2, 8, 0);
		}

		// draw the frame
		cv::imshow("AdReal", frame);
		cv::waitKey(1);

		// pre
		preFrame = frame;
		count++;
	}
	return 0;
}
