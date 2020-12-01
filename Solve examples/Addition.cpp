#include "Addition.h"
#include<sstream>
int Addition::get_right_answer()
{
	return answer;
}
void Addition::create_example(int _left, int _right)
{
	right = _right;
	left = _left;
	answer = left + right;
}

std::string Addition::show_example()
{

	std::ostringstream output;
	output << left << "+" << right << "=";
	return output.str();
}

int Addition::get_left()
{
	return left;
}

int Addition::get_right()
{
	return right;
}
