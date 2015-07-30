#include "test.hpp"
#include "tracking_engine.hpp"
#include "img_warper.hpp"
#include "misc.hpp"
#include <iostream>
#include <vector>
#include <opencv2/highgui.hpp>

using namespace cv;
using std::vector;

int main() {
	// read video
	const std::string video_filename = "resource/video_simple.mp4";
	cv::VideoCapture capture(video_filename);
	if (!capture.isOpened()) {
		std::cout << "Video file could not be opened" << std::endl;
		return -1;
	}

	// Create window to display video frames
	cv::namedWindow("AdReal", WINDOW_AUTOSIZE);

	// Create tracking engine
	TrackingEngine engine;

	// Create image wrapper
	cv::Mat img = cv::imread("resource/indoor.jpg");
	ImgWarper warper(img);

	// Process each video frame
	Mat frame_c, frame, frame_i;
	capture >> frame_c;
	cvtColor(frame_c, frame, COLOR_BGR2GRAY);

	// init tracking point
	std::vector<cv::Point2f> unorderedPts, orderedPts;
	unorderedPts.push_back(Point2f(1016, 166));
	unorderedPts.push_back(Point2f(1480, 158));
	unorderedPts.push_back(Point2f(1470, 796));
	unorderedPts.push_back(Point2f(986, 774));

	sortPtsClockwise(unorderedPts, orderedPts);
	for(int i=0; i<4; i++) {
		engine.addTrackingPoint(orderedPts[i],frame);
	}

	// output points
	vector<Point2f> points;

	while (1) {
		capture >> frame_c;
		if (frame_c.empty()) {
			std::cout << "Finished processing the video" << std::endl;
			break;
		}
		cvtColor(frame_c, frame, COLOR_BGR2GRAY);

		//Track!!
		engine.trackAllPoints(frame,points);

		// visualize the point
		for (int i = 0; i < (int) (points.size()); i++) {
			circle(frame_c, points[i], 3, Scalar(0, 255, 0), 2, 8, 0);
		}

		// compute the homo
		warper.computeHomograpy(points);
		warper.embedAd(frame_c, frame_i);

		// draw the frame
		//cv::imshow("AdReal", frame_i);
		//cv::waitKey(1);
	}
	return 0;
}
