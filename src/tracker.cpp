#include "tracker.hpp"

void Tracker::trackPoints(cv::Mat &prevImg, std::vector<cv::Point> &prevPts,
		 	 	 	 	  cv::Mat &currImg, std::vector<cv::Point> &currPts, std::vector<uchar> &trackStatus) {
	std::vector<double> err;
	cv::Size winSize = cv::Size(this->windowSize, this->windowSize);
	cv::TermCriteria criteria = cv::TermCriteria(cv::TermCriteria::COUNT+cv::TermCriteria::EPS, this->maxIterations, this->epsilon);
	cv::calcOpticalFlowPyrLK(prevImg, currImg, prevPts, currPts, trackStatus, err, winSize, this->maxLevel, criteria, this->flags, this->minEigThresh);
	this->currPts_ = &currPts;
	this->trackStatus_ = &trackStatus;

}
