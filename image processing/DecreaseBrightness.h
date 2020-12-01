#pragma once
#include"ImageProcessing.h"
#include "opencv2/opencv.hpp"
class DecreaseBrightness final :public ImageProcessing {
public:
	DecreaseBrightness() = default;
	DecreaseBrightness(size_t count) :ImageProcessing(count) {};
	~DecreaseBrightness() = default;
	cv::Vec3b ProcessPixel(const cv::Mat& src, int x, int y)override;
};