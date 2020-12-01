#include <iostream>
#include <string>
#include "libbitmap.h"
#include "rotation_bmp.h"
using namespace std;

static size_t  remainder(const Bitmap &BMP) {
	return (BMP.m_width * 3 % 4 > 0) ? (4 - BMP.m_width * 3 % 4) : 0;
}
static size_t size(const Bitmap &BMP) {
	return BMP.m_height*BMP.m_width * 3 + remainder(BMP) * BMP.m_height;
}
static uint8_t& coeffRef(const Bitmap &BMP,size_t rowIdx, int colIdx,size_t number) {
	return BMP.m_buffer[rowIdx*(BMP.m_width * 3 + remainder(BMP)) + colIdx * 3+number];
}
void rotation_bmp:: vertical_rotation(Bitmap &BMP){
	if (BMP.m_width==0||BMP.m_height==0)
		return ;
	for(size_t ind_rows=0;ind_rows<BMP.m_height;ind_rows++)
		for (int ind_cols = 0; ind_cols < BMP.m_width/2; ind_cols++) {
			std::swap(coeffRef(BMP,ind_rows, ind_cols, 0),coeffRef(BMP,1 + ind_rows, -ind_cols, -3 - remainder(BMP)));
			std::swap(coeffRef(BMP,ind_rows, ind_cols, 1), coeffRef(BMP,1 + ind_rows, -ind_cols, -2 - remainder(BMP)));
			std::swap(coeffRef(BMP,ind_rows, ind_cols, 2), coeffRef(BMP,1 + ind_rows, -ind_cols, -1 - remainder(BMP)));
		}
}
void rotation_bmp::horizon_rotation(Bitmap &BMP){
	if (BMP.m_width == 0 || BMP.m_height == 0)
		return;
	for (size_t ind_rows = 0; ind_rows < BMP.m_height /2; ind_rows++)
		for (size_t ind_cols = 0; ind_cols < BMP.m_width ; ind_cols++) {
			std::swap(coeffRef(BMP, ind_rows, ind_cols, 0), coeffRef(BMP, BMP.m_height - ind_rows - 1, ind_cols,0));
			std::swap(coeffRef(BMP, ind_rows, ind_cols, 1), coeffRef(BMP, BMP.m_height - ind_rows - 1, ind_cols, 1));
			std::swap(coeffRef(BMP, ind_rows, ind_cols, 2), coeffRef(BMP, BMP.m_height - ind_rows - 1, ind_cols, 2));
		}
}

void  rotation_bmp::rotate_90(Bitmap &BMP) {
	if (BMP.m_width == 0 || BMP.m_height == 0)
		return;
	size_t width = BMP.m_height, height = BMP.m_width;
	size_t remainder = (width * 3 % 4 > 0) ? (4 - width * 3 % 4) : 0;
	size_t size = BMP.m_height*BMP.m_width * 3 + remainder * height;
	uint8_t* m_buffer= new uint8_t[size];
	for (size_t ind_rows=0;ind_rows<height;ind_rows++)
		for (size_t ind_cols = 0; ind_cols < width; ind_cols++) {

			m_buffer[ind_rows*(width * 3 + remainder) + ind_cols * 3 + 0] =coeffRef(BMP,BMP.m_height - ind_cols - 1,ind_rows, 0);
			m_buffer[ind_rows*(width * 3 + remainder) + ind_cols * 3 + 1] = coeffRef(BMP,BMP.m_height - ind_cols - 1, ind_rows, 1);
			m_buffer[ind_rows*(width * 3 + remainder) + ind_cols * 3 + 2] = coeffRef(BMP,BMP.m_height - ind_cols - 1, ind_rows, 2);
		}
	BMP.clear();
	BMP.m_height = height;
	BMP.m_width = width;
	BMP.m_buffer = m_buffer;
}
void  rotation_bmp::rotate_180(Bitmap &BMP) {
	if (BMP.m_width == 0 || BMP.m_height == 0)
		return;
	for(size_t i=0;i<2;i++)
		rotate_90(BMP);
	
}
void rotation_bmp::rotate_270(Bitmap &BMP) {
	if (BMP.m_width == 0 || BMP.m_height == 0)
		return;
	for (size_t i = 0; i < 3; i++)
		rotate_90(BMP);
}

