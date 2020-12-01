#pragma once
#include <iostream>
#include "libbitmap.h"
namespace rotation_bmp {
		void  rotate_90(Bitmap &BMP);
		void  rotate_180(Bitmap &BMP);
		void  rotate_270(Bitmap &BMP);

		void vertical_rotation(Bitmap &BMP);
		void  horizon_rotation(Bitmap &BMP);
}
