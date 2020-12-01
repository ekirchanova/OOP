#pragma once
#include "BlurInfo.h"
class BlurringImage final
{
	static cv::Rect create_region(int x, int y, int width, int height);
public:
	static cv::Mat blur_image(const BlurInfo& cur_info);
	
};