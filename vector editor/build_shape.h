#pragma once
#include"create_shape.h"
#include<map>
class  BuilderShape {
	static enum class struct_string_info
	{
		type_name = 0,
		other,
		total_number = 5
	};
	static std::map< std::string, shape> builder_shapes;
public:
	static std::vector<std::shared_ptr <Shape>> build_shapes(const std::vector<std::string>& data);
};
