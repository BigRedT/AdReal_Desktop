#include "tracking_engine.hpp"

TrackingEngine engine;

bool engine_init() {
	//engine initialization
	return true;
}

bool engine_addPoints() {
	cv::Point2f point;
	cv::Mat frame;
	engine.addTrackingPoint(point, frame);
	return true;
}

bool engine_trackPoints() {
	std::vector<Point2f> points;
	cv::Mat frame;
	engine.trackAllPoints(frame, points);
	return true;
}
