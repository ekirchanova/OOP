#pragma once
#include <cmath>
class Coordinate final {
public:
	Coordinate(const double _x, const double _y) :x(_x), y(_y) {};
	double x;
	double y;
	void translate(const double dx, const double dy) {
		x += dx;
		y += dy;
	}
	void scale(const double sx, const double sy) {
		x = x*sx;
		y = y*sy;
	}
	void rotate(const double angle) {
		const Coordinate old_coord(*this);
		x = old_coord.x *std::cos(angle) - old_coord.y * std::sin(angle);
		y = old_coord.x * std::sin(angle) + old_coord.y * std::cos(angle);
	}
};
