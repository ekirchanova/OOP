#include "Multiplication.h"
#include<sstream>
int Multiplication::get_right_answer()
{
	return answer;
}
void Multiplication::create_example(int _left, int _right)
{
	right = _right;
	left = _left;
	answer = left * right;
}

std::string Multiplication::show_example()
{

	std::ostringstream output;
	output << left << "x" << right << "=";
	return output.str();
}

int Multiplication::get_left()
{
	return left;
}

int Multiplication::get_right()
{
	return right;
}
