#pragma once
#include <string>

class Operations
{
public:
	virtual ~Operations()=default;
	virtual void create_example(int _left, int _right) = 0;
	virtual std::string show_example()=0;
	virtual int get_right_answer() = 0;
	virtual int get_left() = 0;
	virtual int get_right() = 0;
};
