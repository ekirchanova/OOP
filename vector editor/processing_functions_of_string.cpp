#include"processing_functions_of_string.h"
#include <sstream>
#include <iterator>
#include <algorithm>

std::vector<std::string> processing_functions_of_string:: parse_string(const std::string& data)
{
	std::vector <std::string>cur;
	std::istringstream ist(data);
	std::copy(std::istream_iterator<std::string>(ist), {}, std::back_inserter(cur));
	return cur;
}
double processing_functions_of_string::create_double(const std::string& str) {
	try {
		return stod(str);
	}
	catch (...) {
		return {};
	}
}
std::pair<std::string, std::string> processing_functions_of_string::create_type_and_name(const std::string& cur_str) {
	auto pos1 = cur_str.find("[");
	auto pos2 = cur_str.find("]");
	if (pos1 == std::string::npos || pos2 == std::string::npos || pos1 + 1 == pos2 || pos2 != cur_str.size() - 1) return std::pair<std::string, std::string>();
	std::string cur_type = cur_str.substr(0, pos1);
	std::string cur_name = cur_str.substr(pos1 + 1, pos2);
	return std::make_pair(cur_type, cur_name);
};
std::vector<double> processing_functions_of_string::create_numbers(const std::vector<std::string>& data, size_t number) {
	std::vector<double> numbers;
	numbers.resize(data.size() - number);
	std::transform(data.begin() + number, data.end(), numbers.begin(), processing_functions_of_string::create_double);
	return numbers;
}