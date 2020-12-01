#include "processing_functions_of_string.h"
#include <sstream>
#include <iterator>
#include <iomanip>
#include <algorithm>

std::vector<std::string> processing_functions_of_string::parse_string(const std::string& data)
{
	std::vector <std::string>cur;
	std::istringstream ist(data);
	std::copy(std::istream_iterator<std::string>(ist), {}, std::back_inserter(cur));
	return cur;
}

std::time_t processing_functions_of_string::create_time(const std::string& cur_str)
{
	if (cur_str.size() < 8)return time_t();
	std::tm time = {};
	std::istringstream in(cur_str);
	in >> std::get_time(&time, "%Y-%m-%dT%X");
	return std::mktime(&time);
}

size_t processing_functions_of_string::create_size_t(const std::string& str)
{
	try {
		return stoi(str);
	}
	catch (...) {
		return {};
	}
}

std::vector<size_t> processing_functions_of_string::create_numbers(const std::vector<std::string>& data, size_t number)
{
	std::vector<size_t> numbers;
	numbers.resize(data.size() - number);
	std::transform(data.begin() + number, data.end(), numbers.begin(), create_size_t);
	return numbers;
}
