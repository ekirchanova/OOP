#pragma once
#include <iostream>

class WorkerWithStream final
{
public:
	static bool write_in_stream(std::ostream& output, const std::string& str);
	static enum class answers { wrong_answer=-1, linefeed=-2,bad_stream=-3};
	static int set_answer(std::istream& input);
};
