#pragma once
#include"ImageProcessing.h"
#include "opencv2/opencv.hpp"

class IncreaseContrast final :public ImageProcessing {
public:
	IncreaseContrast() = default;
	IncreaseContrast(size_t count) :ImageProcessing(count) {};
	~IncreaseContrast() = default;
	cv::Vec3b ProcessPixel(const cv::Mat& src, int x, int y)override;
};