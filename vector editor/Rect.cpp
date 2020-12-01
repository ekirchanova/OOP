#include"Rect.h"
#include<sstream>
namespace {
	bool check_changes(const double x, const double y) {
		return x == std::numeric_limits<double>::infinity() || y == std::numeric_limits<double>::infinity() || x == NAN || y == NAN;
	}
	enum class struct_line_rect
	{
		coord_x_first_point,
		coord_y_first_point,
		coord_x_second_point,
		coord_y_second_point
	};
}
Rect::Rect(const std::string& _name, const std::vector<double>& points) : name(_name),
first_point(Coordinate(points[size_t(struct_line_rect::coord_x_first_point)], points[size_t(struct_line_rect::coord_y_first_point)])),
second_point(Coordinate(points[size_t(struct_line_rect::coord_x_second_point)], points[size_t(struct_line_rect::coord_y_second_point)])) {};

void Rect::rotate(const double angle)
{
	first_point.rotate(angle);
	second_point.rotate(angle);

}
void Rect::translate(const double dx, const double dy) {
	if (check_changes(dx, dy)) return;
	first_point.translate(dx, dy);
	second_point.translate(dx, dy);
}
void Rect::scale(const double sx, const double sy) {
	if (check_changes(sx, sy)) return;
	first_point.scale(sx, sy);
	second_point.scale(sx, sy);
}
bool Rect::check_match_shape(const std::string& type, const std::string& needed_name)
{
	return type == "rect" && needed_name == name;
}
std::string Rect::convert_to_vector_string()
{
	std::ostringstream output;
	output << "rect" << "[" << name << "] ";
	output << first_point.x << " " << first_point.y << " ";
	output << second_point.x << " " << second_point.y;
	return output.str();

}