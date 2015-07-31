#include "misc.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <assert.h>
#include <cmath>

bool compfun(cv::Point2f a, cv::Point2f b) {
	return (a.y < b.y);
}

void sortPtsClockwise(std::vector<cv::Point2f> &unorderedPts,
		std::vector<cv::Point2f> &orderedPts) {
	//assert(unorderedPts.size() == 4);

	int order[4] = { 0, 1, 2, 3 };

	std::sort(unorderedPts.begin(), unorderedPts.end(), compfun);

	// Smaller x of top row goes first
	if (unorderedPts.at(0).x > unorderedPts.at(1).x) {
		order[0] = 1;
		order[1] = 0;
	}

	// Larger x of bottom row goes first
	if (unorderedPts.at(3).x > unorderedPts.at(2).x) {
		order[2] = 3;
		order[3] = 2;
	}

	for (int i = 0; i < 4; i++) {
		orderedPts.push_back(unorderedPts.at(order[i]));
	}
}

static double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0)
{
	double dx1 = pt1.x - pt0.x;
	double dy1 = pt1.y - pt0.y;
	double dx2 = pt2.x - pt0.x;
	double dy2 = pt2.y - pt0.y;
	return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

void findRectangles(const cv::Mat& frame, std::vector<quad> &quads) {

	// Use Canny instead of threshold to catch squares with gradient shading
	cv::Mat bw;
	cv::Canny(frame, bw, 0, 50, 5);
	cv::namedWindow("Canny",1);
	cv::imshow("Canny",bw);
	cv::waitKey(0);

	// Find contours
	std::vector<std::vector<cv::Point> > contours;
	cv::findContours(bw.clone(), contours, CV_RETR_EXTERNAL,
			CV_CHAIN_APPROX_SIMPLE);

	std::vector<cv::Point> approx;
	cv::Mat dst = frame.clone();

	for (int i = 0; i <(int) contours.size(); i++) {
		// Approximate contour with accuracy proportional
		// to the contour perimeter
		cv::approxPolyDP(cv::Mat(contours[i]), approx,
				cv::arcLength(cv::Mat(contours[i]), true) * 0.02, true);

		// Skip small or non-convex objects
		if (std::fabs(cv::contourArea(contours[i])) < 100
				|| !cv::isContourConvex(approx))
			continue;

		if (approx.size() == 4) {
			// Number of vertices of polygonal curve
			int vtc = approx.size();

			// Get the cosines of all corners
			std::vector<double> cos;
			for (int j = 2; j < vtc+1; j++)
				cos.push_back(angle(approx[j % vtc], approx[j - 2], approx[j - 1]));

			// Sort ascending the cosine values
			std::sort(cos.begin(), cos.end());

			// Get the lowest and the highest cosine
			double mincos = cos.front();
			double maxcos = cos.back();

			// Use the degrees obtained above and the number of vertices
			// to determine the shape of the contour
			if (mincos >= -0.1 && maxcos <= 0.3)
				quads.push_back(quad(approx));
		}
	}
}
