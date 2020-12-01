#include "ImageProcessing.h"
#include "opencv2/opencv.hpp"
#include <functional>
#include <mutex>
namespace
{
	enum class number_cur_part {first_part=0,second_part=1 };
	std::mutex Image_mutex;
}
int ImageProcessing::part_size(const cv::Mat& src, const size_t number_part) const
{
	if(number_part==size_t(number_cur_part::first_part))
	{
		return src.rows / parts_count + src.rows%parts_count;
	}
	return src.rows/parts_count;
}

cv::Rect ImageProcessing::create_region(const cv::Mat& src,const size_t number_part) const
{
	int _part_size = part_size(src, number_part);
	return cv::Rect{ 0,calculate_y(number_part,src) , src.cols ,  _part_size };
}
int ImageProcessing::calculate_y(size_t number_part, const cv::Mat& src) const
{
	if(number_part==size_t(number_cur_part::second_part))
	{
		return (number_part)*part_size(src,size_t(number_cur_part::first_part));
	}
	return (number_part)*part_size(src,number_part);
}
ImageProcessing::ImageProcessing():threads_pool(thread_pool::ThreadPool()){
	parts_count = threads_pool.max_size();
}
ImageProcessing::ImageProcessing( int threads_cnt): threads_pool(thread_pool::ThreadPool(threads_cnt))
{
	parts_count = threads_pool.max_size();
}
void  ImageProcessing::thread_process(const cv::Mat& src,cv::Mat dst)
{
	std::lock_guard<std::mutex> guard(Image_mutex);
	size_t count = 0;
	for (size_t i = 0; i < src.cols; ++i) {
		for (size_t j = 0; j < src.rows; ++j) {
			dst.at<cv::Vec3b>(cv::Point(i,j)) = ProcessPixel(src, i,j);
			++count;
		}
	}
}

bool ImageProcessing::Process(const cv::Mat& src, cv::Mat& dst)
{
	if(src.empty()||dst.empty()) return false;
	for (size_t i = 0; i < parts_count; ++i) {
		cv::Rect cur_region = create_region(src, i);
		threads_pool.alloc([=] {ImageProcessing::thread_process(src(cur_region),dst(cur_region)); return true; } );
	}
	return true;
}



