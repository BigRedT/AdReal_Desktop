#ifndef _MISC_HPP
#define _MISC_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <opencv2/core.hpp>

struct quad {
	cv::Point2f points[4];
	quad() {}
	quad(std::vector<cv::Point>& points_) {
		for(int i=0; i<4; i++) {
			points[i] = points_.at(i);
		}
	}
};

void sortPtsClockwise(std::vector<cv::Point2f> &unorderedPts, std::vector<cv::Point2f> &orderedPts);

void findRectangles(const cv::Mat& frame, std::vector<quad> &quads);


#endif
