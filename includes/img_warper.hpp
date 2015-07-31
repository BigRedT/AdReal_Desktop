#ifndef _IMG_WARPER_HPP_
#define _IMG_WARPER_HPP_

#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>

class ImgWarper {
public:
	cv::Mat ad;
	std::vector<cv::Point2f> dst_rect_corners;
	std::vector<cv::Point2f> src_rect_corners;
	cv::Mat_<double> H;

public:
	ImgWarper(const cv::Mat &ad_) {
		ad = ad_.clone();

		// Set the target rectangle corners
		int X[] = {5, ad.cols-5, ad.cols-5, 5};
		int Y[] = {5, 5, ad.rows-5, ad.rows-5};
		for(int i= 0; i < 4; i++) {
			dst_rect_corners.push_back(cv::Point2f(X[i],Y[i]));
		}
	}

	void computeHomograpy(const std::vector<cv::Point2f> &src_rect_corners_);

	void embedAd(const cv::Mat &img, cv::Mat &ad_img);

};

#endif
