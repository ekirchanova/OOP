#include"RotateBuilder.h"
#include "processing_functions_of_string.h"
#include"Rotate.h"
namespace {
	enum class struct_command
	{
		type_name_shape = 1,
		first_change = 2,
		size_rotate = 3
	};

	bool check_parameters(const std::pair<std::string, std::string>& type_name)
	{
		auto& [type, name] = type_name;
		return type.empty() && name.empty();
	}
}
std::shared_ptr<Command> RotateBuilder::creator_command(const std::vector<std::string>& cur_data)
{
	if (cur_data.size() != size_t(struct_command::size_rotate)) return nullptr;
	auto type_name_shape = processing_functions_of_string::create_type_and_name(cur_data[size_t(struct_command::type_name_shape)]);
	if (check_parameters(type_name_shape)) return nullptr;
	double change = processing_functions_of_string::create_double(cur_data[size_t(struct_command::first_change)]);
	return std::make_shared<Rotate>(type_name_shape, change);
}
