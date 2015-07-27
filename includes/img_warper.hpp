#ifndef _IMG_WARPER_HPP_
#define _IMG_WARPER_HPP_

#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>

class ImgWarper {
public:
	cv::Mat ad;
	std::vector<cv::Point> dst_rect_corners;
	std::vector<cv::Point> src_rect_corners;
	cv::Mat_<double> H;

public:
	ImgWarper(const cv::Mat &ad_) {
		ad = ad_.clone();

		// Set the target rectangle corners
		int X[] = {0, ad.cols, ad.cols, 0};
		int Y[] = {0, 0, ad.rows, ad.rows};
		for(int i= 0; i < 4; i++) {
			dst_rect_corners.push_back(cv::Point(X[i],Y[i]));
		}
	}

	void computeHomograpy(const std::vector<cv::Point> &src_rect_corners_);

	void embedAd(const cv::Mat &img, cv::Mat &ad_img);

};

#endif
