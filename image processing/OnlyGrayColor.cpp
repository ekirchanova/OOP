#include "OnlyGrayColor.h"

cv::Vec3b OnlyGrayColor::ProcessPixel(const cv::Mat& src, int x, int y)
{
	const cv::Vec3b input = src.at<cv::Vec3b>(cv::Point(x, y));
	int overage_value = (input[0] + input[1] + input[2])/3;
	cv::Vec3b output;
	output[0] = overage_value;
	output[1] = overage_value;
	output[2] = overage_value;
	return output;
}
