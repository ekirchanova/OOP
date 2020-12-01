#include "IncreaseContrast.h"
namespace
{
	const int CONST_INCREASE_CONTRAST = 2;
}
cv::Vec3b IncreaseContrast::ProcessPixel(const cv::Mat& src, int x, int y)
{
	cv::Vec3b output = src.at<cv::Vec3b>(cv::Point(x, y));
	output[0] *= CONST_INCREASE_CONTRAST;
	output[1] *= CONST_INCREASE_CONTRAST;
	output[2] *= CONST_INCREASE_CONTRAST;
	return output;
}
