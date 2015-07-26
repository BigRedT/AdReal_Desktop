#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>



int main2() {
	const std::string video_filename = "/home/tanmay/Downloads/video_simple.mp4";
	// read video
	cv::VideoCapture capture(video_filename);
	if(!capture.isOpened()) {
		std::cout << "Video file could not be opened" << std::endl;
		return -1;
	}

	// Create window to display video frames
	cv::namedWindow("AdReal",1);
	// Process each video frame
	cv::Mat frame;
	while(1) {
		capture >> frame;
		if(frame.empty()) {
			std::cout << "Finished processing the video" << std::endl;
			break;
		}

		/*
		 *
		 * Detection and Tracking Code goes here
		 *
		 */

		cv::imshow("AdReal",frame);
		cv::waitKey(1);
	}
	return 0;
}
