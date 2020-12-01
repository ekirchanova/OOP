//#include"create_shape.h"
//#include"Coordinate.h"
//#include<algorithm>
//namespace {
//	enum class struct_shape
//	{
//		count_double_point=4
//	};
//	
//	
//	 bool check_struct(const std::string &name, const std::vector<double>& points) {
//		 return !name.size() || points.size() != size_t(struct_shape::count_double_point);
//	 }
//}
//
//
//
//std::shared_ptr <Shape> LineOrRectCreator::create_shape(const std::pair<std::string, std::string>&type_name ,const std::vector<std::string>& data) {
//	auto [type, name] = type_name;
//	
//	if (check_struct(name, points))return nullptr;
//	Coordinate first_point(points[size_t(struct_line_rect::coord_x_first_point)], points[size_t(struct_line_rect::coord_y_first_point)]);
//	Coordinate second_point(points[size_t(struct_line_rect::coord_x_second_point)], points[size_t(struct_line_rect::coord_y_second_point)]);
//	if (!type.compare("line")) {
//		return std::make_shared<Line>(name, first_point, second_point);
//	}
//	else {
//		return std::make_shared<Rect>(name, first_point, second_point);
//	}
//}
//std::shared_ptr <Shape> EllipseCreator::create_shape(const std::pair<std::string, std::string>& type_name,const std::vector<std::string>& data) {
//	auto [type, name] = type_name;
//	if (check_struct(name, points))return nullptr;
//	Coordinate first_point(points[size_t(struct_ellipse::coord_x_center)], points[size_t(struct_ellipse::coord_y_center)]);
//	double height = points[size_t(struct_ellipse::height)];
//	double width = points[size_t(struct_ellipse::widht)];
//	return std::make_shared<Ellipse>(name, first_point,height,width);
//}