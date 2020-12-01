#include "Numbers.h"
#include <numeric>
#include <ctime>

Numbers::Numbers(int range)
{
	srand(time(0));
	left_numbers = std::vector<int>(range);
	right_numbers = std::vector<int>(range);
	std::iota(right_numbers.begin(), right_numbers.end(), 0);
	std::iota(left_numbers.begin(), left_numbers.end(), 0);
}

size_t Numbers::empty() const
{
	return right_numbers.empty()&&left_numbers.empty();
}


int Numbers::get_random_left()
{
	size_t number_random_number = rand() %( left_numbers.size());
	return left_numbers[number_random_number];
}

int Numbers::get_random_right()
{
	size_t number_random_number = rand() %(right_numbers.size());
	return right_numbers[number_random_number];
}

void Numbers::add_left(int left)
{
	left_numbers.push_back(left);
}

void Numbers::add_right(const int right)
{
	right_numbers.push_back(right);
}
