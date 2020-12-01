#pragma once
#include"GUI.h"
#include "opencv2/highgui/highgui.hpp"

class ApplicationBlurringImage final
{
	static GUI gui;
	static void call_back_mouse(int event, int x, int y, int flags, void* userdata);
	static void call_back_trackbar_width(int width, void* userdata);
	static void call_back_trackbar_height(int height, void* userdata);
public:
	static void start(const cv::Mat& img, size_t delay = 0, size_t default_height = 0, size_t default_width = 0);

};