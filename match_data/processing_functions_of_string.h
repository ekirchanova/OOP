#pragma once
#include<vector>
#include<string>
#include <ctime>
 namespace processing_functions_of_string
 {
	 std::vector<std::string> parse_string(const std::string& data);
	 std::time_t create_time(const std::string& cur_str);
	 size_t create_size_t(const std::string& str);
	 std::vector<size_t> create_numbers(const std::vector<std::string>& data, size_t number);
 }