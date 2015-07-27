#include "test.hpp"
#include "corner_detector.hpp"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video/tracking.hpp>


int main() {
	const std::string video_filename = "resource/video_simple.mp4";
	// read video
	cv::VideoCapture capture(video_filename);
	if(!capture.isOpened()) {
		std::cout << "Video file could not be opened" << std::endl;
		return -1;
	}

	// Create window to display video frames
	cv::namedWindow("AdReal",1);

	// detector
	CornerDetector detector;

	// kalman filter
	KalmanFilter KF(8, 8, 8);  //numState, numMeasure, numControl
	setIdentity(KF.measurementMatrix);
	setIdentity(KF.transitionMatrix);
	setIdentity(KF.controlMatrix);
	KF.processNoiseCov = Mat::eye(8,8,CV_32F)*0.001;
	KF.measurementNoiseCov = Mat::eye(8,8,CV_32F)*0.00001;

	Mat delta(8, 1, CV_32F);
	Mat measure(8, 1, CV_32F);

	// Process each video frame
	cv::Mat frame;
	int count = 0;
	while(1) {
		capture >> frame;
		if(frame.empty()) {
			std::cout << "Finished processing the video" << std::endl;
			break;
		}

		// run tracker
		Mat delta;

		KF.predict(delta);

		count++;
		if(count>=50) {
			count = 0;
			// run detector
			KF.correct(measure);
		}
		else {
			KF.statePost = KF.statePre;
		}

		// add the point
		circle(frame, Point(KF.statePost(0,0), KF.statePost(1,0)), 3, Scalar(0, 255, 0), 2, 8, 0);
		circle(frame, Point(KF.statePost(2,0), KF.statePost(3,0)), 3, Scalar(0, 255, 0), 2, 8, 0);
		circle(frame, Point(KF.statePost(4,0), KF.statePost(5,0)), 3, Scalar(0, 255, 0), 2, 8, 0);
		circle(frame, Point(KF.statePost(6,0), KF.statePost(7,0)), 3, Scalar(0, 255, 0), 2, 8, 0);

		// draw the frame
		cv::imshow("AdReal",frame);
		cv::waitKey(1);
	}
	return 0;
}
