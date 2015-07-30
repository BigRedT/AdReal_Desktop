#include "misc.hpp"


void sortPtsClockwise(const std::vector<cv::Point2f> &unorderedPts, std::vector<cv::Point2f> &orderedPts) {
	assert(unorderedPts.size() == 4);
	int order[4] = {0,1,2,3};
	int tmp;
	for(int i=1; i < 4; i++) {
		for(int j=0; j<i; j++) {
			if(unorderedPts.at(i).y > unorderedPts.at(j).y) {
				tmp = order[i];
				order[i] = order[j];
				order[j] = tmp;
			}
		}
	}

	// Smaller x of top row goes first
	if(unorderedPts.at(order[0]).x > unorderedPts.at(order[1]).x) {
		tmp = order[0];
		order[0] = order[1];
		order[1] = tmp;
	}

	// Larger x of bottom row goes first
	if(unorderedPts.at(order[3]).x > unorderedPts.at(order[2]).x) {
		tmp = order[3];
		order[3] = order[2];
		order[2] = tmp;
	}

	for(int i=0; i<4; i++) {
		orderedPts.push_back(unorderedPts.at(order[i]));
	}
}
