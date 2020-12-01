#include"Ellipse.h"
#include<sstream>
namespace {
	bool check_changes(const double x, const double y) {
		return x == std::numeric_limits<double>::infinity() || y == std::numeric_limits<double>::infinity() || x == NAN || y == NAN;
	}
	
	enum class struct_ellipse
	{
		coord_x_center,
		coord_y_center,
		width, height
	};
}

Ellipse::Ellipse(const std::string& _name, const std::vector<double>& points) : name(_name),
center(Coordinate(points[size_t(struct_ellipse::coord_x_center)], points[size_t(struct_ellipse::coord_y_center)])),
width(points[size_t(struct_ellipse::width)]), height(points[size_t(struct_ellipse::height)]) {};
void Ellipse::rotate(const double angle) {
	center.rotate(angle);
}
void Ellipse::translate(const double dx, const double dy) {
	if (check_changes(dx, dy)) return;
	center.translate(dx, dy);
}
void Ellipse::scale(const double sx, const double sy) {
	if (check_changes(sx, sy)) return;
	height = height * sy;
	width = width * sx;
}

bool Ellipse::check_match_shape(const std::string& type, const std::string& needed_name)
{
	return type=="ellipse" && needed_name==name;
}

std::string Ellipse::convert_to_vector_string()
{
	std::ostringstream output;
	output << "ellipse" << "[" << name << "] ";
	output << center.x << " " << center.y << " ";
	output << width << " " << height;
	return output.str();
}