#ifndef _CORNER_DETECTOR_HPP
#define _CORNER_DETECTOR_HPP

#include "opencv2/imgproc.hpp"

using namespace cv;

class CornerDetector {

public:
	void detectCorner(const Mat& img, const Point& searchCenter,
					  const int searchSize, Point& searchResult);

private:
	int blockSize = 2;
	int apertureSize = 3;
	double k = 0.04;
};

#endif
