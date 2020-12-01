#pragma once
#include"ImageProcessing.h"
#include "opencv2/opencv.hpp"
class OnlyGreenColor final :public ImageProcessing {
public:
	OnlyGreenColor() = default;
	OnlyGreenColor(size_t count) :ImageProcessing(count) {};
	~OnlyGreenColor() = default;
	cv::Vec3b ProcessPixel(const cv::Mat& src, int x, int y)override;

};