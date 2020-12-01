#include "OnlyGreenColor.h"

cv::Vec3b OnlyGreenColor::ProcessPixel(const cv::Mat& src, int x, int y)
{
	cv::Vec3b output;
	output[0] = 0;
	output[1] = src.at<cv::Vec3b>(cv::Point(x, y))[1];
	output[2] = 0;
	return output;
}
