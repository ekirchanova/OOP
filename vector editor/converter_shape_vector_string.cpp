#include "converter_shape_vector_string.h"
std::vector<std::string> converter_from_shape_to_vector_string::convert(const std::vector<std::shared_ptr<Shape>>& shapes)
{
	if (!shapes.size()) return std::vector<std::string>();
	std::vector<std::string> result;
	for (auto sh_cur_shape : shapes) {
		auto cur_shape = sh_cur_shape.get();
		result.push_back(cur_shape->convert_to_vector_string());
	}
	return result;
}
