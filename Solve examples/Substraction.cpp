#include "Substraction.h"
#include<sstream>
int Substraction::get_right_answer()
{
	return answer;
}
void Substraction::create_example(int _left, int _right)
{
	right = _right;
	left = _left;
	res = left + right;
	answer = left;
}

std::string Substraction::show_example()
{

	std::ostringstream output;
	output << res << "-" << right << "=";
	return output.str();
}

int Substraction::get_left()
{
	return left;
}

int Substraction::get_right()
{
	return right;
}
