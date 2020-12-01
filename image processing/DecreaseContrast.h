#pragma once
#include"ImageProcessing.h"
#include "opencv2/opencv.hpp"

class DecreaseContrast final :public ImageProcessing {
public:
	DecreaseContrast() = default;
	DecreaseContrast(size_t count) :ImageProcessing(count) {};
	~DecreaseContrast() = default;
	cv::Vec3b ProcessPixel(const cv::Mat& src, int x, int y)override;
};