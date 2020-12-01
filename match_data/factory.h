#pragma once
#include"creator.h"
#include<map>
#include <functional>
class Factory {

	enum class struct_string_info
	{
		type = 0,
		other
	};
	static std::map<std::string, std::unique_ptr<Creator>> create_builder_creators();
	static std::map<std::string, std::unique_ptr<Creator>>builder_creators;
public:
	Factory()=default;
	static std::shared_ptr<Product> create_Factory(const std::string& cur_str);
};

