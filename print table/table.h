#pragma once
#include <iostream>
#include <string>
#include <vector> 
class bad_stream final{
public:
	const char* what() const noexcept { return "Your stream is wrong"; };
};
enum class Formatting {
	LEFT, RIGHT, CENTER
};
class table {
public:
	void static read (std::istream &input, std::vector<Formatting> &columns, std::vector<std::vector<std::string> > &table);
	void static print_table(std::ostream &os, const std::vector<Formatting> &columns, const std::vector<std::vector<std::string> > &table);
};