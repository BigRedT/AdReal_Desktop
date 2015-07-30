#ifndef _TRACKING_ENGINE_HPP
#define _TRACKING_ENGINE_HPP

#include <vector>
#include <opencv2/core.hpp>
#include "tracker.hpp"
#include "corner_detector.hpp"

using namespace cv;

class TrackingEngine {

public:
	TrackingEngine();
	~TrackingEngine(){};

	bool addTrackingPoint(const Point2f& point, const Mat& frame);
	bool trackAllPoints(const Mat& cFrame, const Mat& pFrame, std::vector<Point2f>& outPoints);

private:
	CornerDetector detector;
	Tracker tracker;
	KalmanFilter KF;
	int count;

	std::vector<Point2f> points;
};

#endif
