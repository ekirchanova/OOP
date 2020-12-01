#pragma once
#include"ImageProcessing.h"
#include "opencv2/opencv.hpp"
class IncreaseBrightness final :public ImageProcessing {
public:
	IncreaseBrightness() = default;
	IncreaseBrightness(size_t count) :ImageProcessing(count) {};
	~IncreaseBrightness() = default;
	cv::Vec3b ProcessPixel(const cv::Mat& src, int x, int y)override;
};