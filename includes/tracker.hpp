#ifndef _TRACKER_HPP_
#define _TRACKER_HPP_

#include <vector>
#include <opencv2/video.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/optflow.hpp>

class Tracker {

private:
	int windowSize;
	int maxLevel;
	int maxIterations;
	double epsilon;
	int flags;
	double minEigThresh;

public:
	std::vector<cv::Point> *currPts_;
	std::vector<uchar> *trackStatus_;

public:
	Tracker() {
		windowSize = 21;
		maxLevel = 3;
		maxIterations = 30;
		epsilon = 0.01;
		flags = 0 + cv::OPTFLOW_LK_GET_MIN_EIGENVALS;
		minEigThresh = 0;
		currPts_ = NULL;
		trackStatus_ = NULL;
	}

	void trackPoints(const cv::Mat &prevImg, const std::vector<cv::Point> &prevPts,
					 const cv::Mat &currImg, std::vector<cv::Point> &currPts, std::vector<uchar> &trackStatus);
};

#endif
