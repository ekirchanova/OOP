#pragma once
#include <string>
#include<vector>
namespace work_with_stream {
	std::vector<std::string> read_data(std::istream& input);
	void write_data(std::ostream& output, const std::vector<std::string>& data);
}