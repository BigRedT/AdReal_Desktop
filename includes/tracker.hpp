#ifndef _TRACKER_HPP_
#define _TRACKER_HPP_

#include <opencv2/video.hpp>
class Tracker {

private:
	cv::Size winSize = cv::Size(21,21);
	int maxLevel = 3;
	cv::TermCriteria criteria = cv::TermCriteria(cv::TermCriteria::COUNT+cv::TermCriteria::EPS, 30, 0.01);
	int flags = 0;
	double minEigThresh = 0;

public:
	const std::vector<cv::Point> &prevPts_;
	std::vector<cv::Point> &currPts_;
	std::vector<uchar> &trackStatus_;

public:
	void trackPoints(const cv::Mat &prevImg, const std::vector<cv::Point> &prevPts,
					 cv::Mat &currImg, std::vector<cv::Point> &currPts, std::vector<uchar> &trackStatus);
};

#endif
