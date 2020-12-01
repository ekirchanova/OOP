#pragma once
#include"shape.h"
#include"coordinate.h"
#include <vector>

class Ellipse final :public Shape {
	std::string name;
	Coordinate center;
	double height;
	double width;
public:
	Ellipse(const std::string& _name, const std::vector<double>& points);
	void rotate(double angle)override;
	void translate(double dx, double dy)override;
	void scale(double sx, double sy)override;

	bool check_match_shape(const std::string& type, const std::string& needed_name)override;
	std::string convert_to_vector_string()override;

};
