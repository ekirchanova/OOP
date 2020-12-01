#include "OnlyBlueColor.h"

cv::Vec3b OnlyBlueColor::ProcessPixel(const cv::Mat& src, int x, int y)
{
	cv::Vec3b output;
	output[0] = src.at<cv::Vec3b>(cv::Point(x, y))[0];
	output[1] = 0;
	output[2] = 0;
	return output;
}
