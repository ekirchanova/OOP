#include "DecreaseBrightness.h"
namespace
{
	const int CONST_DECREASE_BRIGHTNESS = 20;
}
cv::Vec3b DecreaseBrightness::ProcessPixel(const cv::Mat& src, int x, int y)
{
	cv::Vec3b output = src.at<cv::Vec3b>(cv::Point(x, y));
	output[0] -= CONST_DECREASE_BRIGHTNESS;
	output[1] -= CONST_DECREASE_BRIGHTNESS;
	output[2] -= CONST_DECREASE_BRIGHTNESS;
	return output;
}
