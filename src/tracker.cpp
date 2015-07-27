#include "tracker.hpp"

void Tracker::trackPoints(const cv::Mat &prevImg, const std::vector<cv::Point> &prevPts,
		 	 	 	 	  cv::Mat &currImg, std::vector<cv::Point> &currPts, std::vector<uchar> &trackStatus) {
	std::vector<double> err;
	cv::calcOpticalFlowPyrLK(prevImg, currImg, prevPts, currPts, trackStatus, err,
							 this->winSize, this->maxLevel, this->criteria, this->flags, this->minEigThresh);
	this->prevPts_ = prevPts;
	this->currPts_ = currPts;
	this->trackStatus_ = trackStatus;
}
