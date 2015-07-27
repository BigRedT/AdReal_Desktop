#include "img_warper.hpp"

void ImgWarper::computeHomograpy(const std::vector<cv::Point> &src_rect_corners_) {
	src_rect_corners = src_rect_corners_;
	H = cv::findHomography(src_rect_corners, dst_rect_corners, 0);
}

void ImgWarper::embedAd(const cv::Mat &img, cv::Mat &ad_img) {
	assert(!H.empty());
	cv::warpPerspective(img, ad_img, H, img.size(), cv::INTER_LINEAR|cv::WARP_INVERSE_MAP, cv::BORDER_CONSTANT, cv::Scalar(0,0,0));
}
