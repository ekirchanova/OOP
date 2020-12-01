#include"Line.h"
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

};
Line::Line(const std::string& _name, const std::vector<double>& points) : name(_name),
                                                                          first_point(Coordinate(points[size_t(struct_line_rect::coord_x_first_point)], points[size_t(struct_line_rect::coord_y_first_point)])),
                                                                          second_point(Coordinate(points[size_t(struct_line_rect::coord_x_second_point)], points[size_t(struct_line_rect::coord_y_second_point)])) {};
void Line::rotate(const double angle) {
	first_point.rotate(angle);
	second_point.rotate(angle);
}
void Line::translate(const double dx, const double dy) {
	if (check_changes(dx, dy)) return;
	first_point.translate(dx, dy);
	second_point.translate(dx, dy);
}
void Line::scale(const double sx, const double sy) {
	if (check_changes(sx, sy)) return;
	first_point.scale(sx, sy);
	second_point.scale(sx, sy);
}
bool Line::check_match_shape(const std::string& type, const std::string& needed_name)
{
	return type=="line" && needed_name==name;
}
std::string Line::convert_to_vector_string()
{
	std::ostringstream output;
	output << "line" << "[" << name << "] ";
	output << first_point.x << " " << first_point.y << " ";
	output << second_point.x << " " << second_point.y;
	return output.str();
}