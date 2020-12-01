#include "WorkerWithStream.h"
#include <string>
namespace
{
	int create_int(const std::string& str)
	{
		try
		{
			return std::stoi(str);
		}catch (...)
		{
			return int(WorkerWithStream::answers::wrong_answer);
		}
	}
}
bool WorkerWithStream::write_in_stream(std::ostream& output, const std::string& str)
{
	if (!output) return false;
	output << str << '\n';
	return true;
}
int WorkerWithStream::set_answer(std::istream& input)
{
	if (!input) return  int(answers::bad_stream);
	std::string current_data;
	std::getline(input,current_data);
	if (current_data == "\n") return  int(answers::linefeed);
	return create_int(current_data);
}
