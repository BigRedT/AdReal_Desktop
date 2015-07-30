#include "misc.hpp"
#include <assert.h>

bool compfun(cv::Point2f a, cv::Point2f b) {
	return (a.y < b.y);
};

void sortPtsClockwise(std::vector<cv::Point2f> &unorderedPts, std::vector<cv::Point2f> &orderedPts) {
	//assert(unorderedPts.size() == 4);

	int order[4] = {0,1,2,3};

	std::sort(unorderedPts.begin(), unorderedPts.end(), compfun);

	// Smaller x of top row goes first
	if(unorderedPts.at(0).x > unorderedPts.at(1).x) {
		order[0] = 1;
		order[1] = 0;
	}

	// Larger x of bottom row goes first
	if(unorderedPts.at(3).x > unorderedPts.at(2).x) {
		order[2] = 3;
		order[3] = 2;
	}

	for(int i=0; i<4; i++) {
		orderedPts.push_back(unorderedPts.at(order[i]));
	}
}
