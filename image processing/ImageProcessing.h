#pragma once
#include "opencv2/opencv.hpp"
#include"Thread_Pool.h"
class OnleRedColor;
class ImageProcessing {
protected:
	thread_pool::ThreadPool threads_pool;
	size_t parts_count;
	void thread_process(const cv::Mat& src, cv::Mat dst);
	int part_size(const cv::Mat & src, size_t number_part)const;
	cv::Rect create_region(const cv::Mat& src, size_t number_part)const;
	int calculate_y(size_t number_part, const cv::Mat& src) const;
public:

	ImageProcessing();
	ImageProcessing(int threads_cnt = -1);
	virtual ~ImageProcessing() = default;
	bool Process(const  cv::Mat& src, cv::Mat &dst);
	virtual cv::Vec3b ProcessPixel(const cv::Mat& src, int x, int y) = 0;
};
