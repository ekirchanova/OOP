#include "DecreaseContrast.h"
namespace
{
	const int CONST_DECREASE_CONTRAST = -1;
}
cv::Vec3b DecreaseContrast::ProcessPixel(const cv::Mat& src, int x, int y)
{
	cv::Vec3b output = src.at<cv::Vec3b>(cv::Point(x, y));
	output[0] *= CONST_DECREASE_CONTRAST;
	output[1] *= CONST_DECREASE_CONTRAST;
	output[2] *= CONST_DECREASE_CONTRAST;
	return output;
}
