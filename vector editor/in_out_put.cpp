#include"in_out_put.h"
#include <iterator>
std::vector<std::string> work_with_stream::read_data(std::istream& input) {
	if (!input) return std::vector<std::string>();
	std::vector<std::string>current_data;
	for (std::string str; getline(input, str);) {
		current_data.push_back(str);
	}
	return current_data;
}
void work_with_stream::write_data(std::ostream& output, const std::vector<std::string>& data) {
	if (!output) return;
	std::copy(data.begin(), data.end(), std::ostream_iterator<std::string>(output, "	"));
	output << std::endl;
}