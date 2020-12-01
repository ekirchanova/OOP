#pragma once
#include"ImageProcessing.h"
#include "opencv2/opencv.hpp"
class OnlyGrayColor final :public ImageProcessing {
public:
	OnlyGrayColor() = default;
	OnlyGrayColor(size_t count) :ImageProcessing(count) {};
	~OnlyGrayColor() = default;
	cv::Vec3b ProcessPixel(const cv::Mat& src, int x, int y)override;

};