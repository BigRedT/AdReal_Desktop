#ifndef _MISC_HPP
#define _MISC_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <opencv2/core.hpp>

void sortPtsClockwise(std::vector<cv::Point2f> &unorderedPts, std::vector<cv::Point2f> &orderedPts);

#endif
