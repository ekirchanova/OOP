#pragma once
#include"shape.h"
#include<vector>
#include<string>
#include<memory>
namespace converter_from_shape_to_vector_string {
	std::vector<std::string> convert(const std::vector<std::shared_ptr<Shape>>& shapes);
}