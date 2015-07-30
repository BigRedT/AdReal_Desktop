#include "img_warper.hpp"
#include <opencv2/highgui.hpp>
#include <iostream>

void ImgWarper::computeHomograpy(const std::vector<cv::Point2f> &src_rect_corners_) {
	//assert(src_rect_corners_.size() == 4);
	src_rect_corners = src_rect_corners_;
	H = cv::findHomography(src_rect_corners, dst_rect_corners);
	//std::cout << H << std::endl;
}

void ImgWarper::embedAd(const cv::Mat &img, cv::Mat &embededAd) {
	//assert(!H.empty());

	cv::Mat ad_img;
	cv::warpPerspective(ad, ad_img, H, img.size(), cv::WARP_INVERSE_MAP, cv::BORDER_CONSTANT, cv::Scalar(0,0,0));
	cv::imshow("AdReal",ad_img);
	cv::waitKey(1);

	// create a binary mask
	cv::Mat mask = cv::Mat::zeros(cv::Size(img.rows, img.cols),CV_8UC1);

	cv::Point points[4];
	for(int i=0; i < 4; i++) {
		points[i] = cv::Point(src_rect_corners.at(i).x,src_rect_corners.at(i).y);
	}
	const cv::Point* pts[1] = {points};


	const int npts[] = {4};


	cv::fillPoly(mask, pts, npts, 1, cv::Scalar(1), 8);

	// use binary mask to fill in the add
	embededAd = img.clone();
	for(int i=0; i < mask.rows; i++) {
		for(int j=0; j < mask.cols; j++) {
			if(mask.at<uchar>(i,j)==1) {
				embededAd.at<cv::Vec3b>(i,j) == ad_img.at<cv::Vec3b>(i,j);
			}
		}
	}
}

