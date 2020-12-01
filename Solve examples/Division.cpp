#include "Division.h"
#include<sstream>
int Division::get_right_answer()
{
	return answer;
}
void Division::create_example(int _left, int _right)
{
	right = _right;
	left = _left;
	res = left * right;
	answer = left;
}

std::string Division::show_example()
{
	std::ostringstream output;
	output << res << "/" << right << "=";
	return output.str();
}

int Division::get_left()
{
	return left;
}

int Division::get_right()
{
	return right;
}
