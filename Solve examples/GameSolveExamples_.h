#pragma once
#include"Operations.h"
#include "ScoreAndTime.h"
#include"Numbers.h"
#include <map>
#include <memory>
#include <iostream>

class Game final
{
public:
	static size_t  DefaultRange ;
	static std::vector<char>  DefaultSigns ;
private:
	ScoreAndTime score_and_time;
	Numbers numbers;
	std::vector<char>signs;
	std::istream& input ;
	std::ostream& output;
	
	std::map<char,std::unique_ptr<Operations>> operations_map;
	static void SignalHandler(int signum);
	void print_score();
	Operations* create_example();
	Operations* random_sign();
	bool print_example(Operations* cur_operation);
	bool get_and_check_answer(Operations* cur_operation);
	void handle_wrong_answer(Operations* cur_operation);
	bool check_count_right_answer();
public:
	Game(const std::vector<char>& _signs = DefaultSigns, int original_range = DefaultRange,std::istream&_input=std::cin,std::ostream&_output=std::cout);
	Game(std::istream& _input = std::cin, std::ostream& _output = std::cout, const std::vector<char>& _signs = DefaultSigns, int original_range = DefaultRange);
	bool start();
	
};
