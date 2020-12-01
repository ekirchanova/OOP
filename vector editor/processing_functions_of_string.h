#pragma once
#include<vector>
#include <string>
namespace processing_functions_of_string
{
	std::vector<std::string> parse_string(const std::string& data);
	double create_double(const std::string& str);
	std::pair<std::string, std::string>create_type_and_name(const std::string& cur_str);
	std::vector<double> create_numbers(const std::vector<std::string>& data, size_t number);
};