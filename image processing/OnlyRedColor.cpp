#include"OnlyRedColor.h"
cv::Vec3b OnlyRedColor::ProcessPixel(const cv::Mat& src, int x, int y)
{
	cv::Vec3b output;
	output[0] = 0;
	output[1] = 0;
	output[2] = src.at<cv::Vec3b>(cv::Point(x, y))[2];
	return output;
}