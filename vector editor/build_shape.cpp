#include"build_shape.h"
#include<algorithm>
#include <functional>
#include <stdexcept>
#include "processing_functions_of_string.h"

namespace {
	enum class struct_shape
	{
		first_double = 1,
		count_double_point = 4
		
	};
	void delete_nullptr(std::vector<std::shared_ptr <Shape>>& result) {
		result.erase(std::remove(result.begin(), result.end(), nullptr), result.end());
	};
	bool check_struct(const std::string &name, const std::vector<double>& points) {
		return !name.size() || points.size() != size_t(struct_shape::count_double_point);
	}
	std::map< std::string, shape> create_builder_shape()
	{
		std::map< std::string, shape> builder_shapes;
		builder_shapes.insert(std::make_pair("line", shape::line));
		builder_shapes.insert(std::make_pair("rect", shape::rect));
		builder_shapes.insert(std::make_pair("ellipse", shape::ellipse));
		return builder_shapes;

	}
}
std::map< std::string, shape> BuilderShape::builder_shapes = create_builder_shape();
std::vector<std::shared_ptr <Shape>> BuilderShape::build_shapes(const std::vector<std::string>& data) {
	if (data.empty())return std::vector<std::shared_ptr <Shape>>();
	std::vector<std::shared_ptr <Shape>> shapes;
	for (auto& cur_str : data) {
		std::vector<std::string> cur_data = processing_functions_of_string::parse_string((cur_str));
		std::pair<std::string, std::string> type_name = processing_functions_of_string::create_type_and_name(cur_data[size_t(struct_string_info::type_name)]);
		auto& [type, name] = type_name;
		const std::vector<double> points = processing_functions_of_string::create_numbers(cur_data, size_t(struct_shape::first_double));
		if (check_struct(name,points)) continue;
		try {
			const shape cur_shape = builder_shapes.at(type);
			ShapeCreator creator;
			shapes.push_back(creator.create_shape(cur_shape, name,points));
		}
		catch (const std::out_of_range) {
			continue;
		}
	}
	delete_nullptr(shapes);
	return shapes;
}