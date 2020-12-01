#pragma once
#include"ImageProcessing.h"
#include "opencv2/opencv.hpp"
class OnlyBlueColor final :public ImageProcessing {
public:
	OnlyBlueColor() = default;
	OnlyBlueColor(size_t count) :ImageProcessing(count) {};
	~OnlyBlueColor() = default;
	cv::Vec3b ProcessPixel(const cv::Mat& src, int x, int y)override;

};
