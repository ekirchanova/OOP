#pragma once
#include <string>
class Shape {
public:
	virtual~Shape() = default;
	virtual bool check_match_shape(const std::string& type, const std::string& needed_name)=0;
	virtual void rotate(double angle) = 0;
	virtual void translate(double dx, double dy) = 0;
	virtual void scale(double sx, double dy) = 0;
	virtual std::string convert_to_vector_string() = 0;

};


