#pragma once
#include "Operations.h"

class  Substraction final :public Operations
{
	int left;
	int right;
	int res;
	int answer;
public:
	int get_right_answer()override;
	void create_example(int _left, int _right) override;
	std::string show_example() override;
	int get_left() override;
	int get_right() override;
};
