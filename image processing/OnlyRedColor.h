#pragma once
#include"ImageProcessing.h"
#include "opencv2/opencv.hpp"
class OnlyRedColor final :public ImageProcessing {
public:
	OnlyRedColor()=default;
	OnlyRedColor(size_t count) :ImageProcessing(count) {};
	~OnlyRedColor() = default;
	cv::Vec3b ProcessPixel(const cv::Mat& src, int x, int y)override;

};