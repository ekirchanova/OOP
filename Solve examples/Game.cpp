#include "Game.h"
#include "WorkerWithStream.h"
#include<csignal>
#include<time.h>
#include <numeric>
#include <iostream>
namespace
{
	
}
void GameSolveExamples::print_score()
{
	const time_t start_print_score = time(NULL);
	
	const time_t end_print_score = time(NULL);
	start_game += end_print_score - start_print_score;
}
size_t GameSolveExamples::calculate_score()
{
	return (right_answers * 100) / (right_answers + wrong_answers);
}
time_t GameSolveExamples::calculate_seconds_per_problem(const time_t &end)
{
	return end-start_game/(right_answers+0.) ;
}
size_t GameSolveExamples::game_rand(const size_t cur_range)
{
	size_t rand_number;
	rand_number = random(cur_range) + random(cur_range);
	if (rand_number > cur_range - 1) rand_number = 2 * cur_range - 1 - rand_number;
	return(rand_number);
}
size_t GameSolveExamples::random(const size_t cur_range)
{
	return rand()%cur_range;
}

void GameSolveExamples::fill_numbers()
{
	right_numbers.resize(range);
	std::iota(right_numbers.begin(), right_numbers.end(), 0);
	left_numbers.resize(range);
	std::iota(left_numbers.begin(), left_numbers.end(), 0);
}
void GameSolveExamples::create_example(const std::vector<char>& signs, const int range)
{
	std::srand(time(NULL));
	size_t number_left = game_rand(range);
	size_t number_right = game_rand(range);
	size_t number_sign = random(signs.size());
	size_t res;
	switch (signs.at(number_sign)) {
	case '+':
	default:
		game_answer = left_numbers[number_left] + right_numbers[number_right];
		std::cout<< left_numbers[number_left]<<'+'<< right_numbers[number_right]<<'='<<std::endl;
		break;

	case '-':
		res= left_numbers[number_left] + right_numbers[number_right];
		game_answer = left_numbers[number_left];
		std::cout << res << '-' << right_numbers[number_right] << '=' << std::endl;
		break;

	case 'x':
		game_answer = left_numbers[number_left] * right_numbers[number_right];
		std::cout << left_numbers[number_left] << '*' << right_numbers[number_right] << '=' << std::endl;
		break;
	case '/':
		while (right_numbers[number_right] == 0)
			number_right = random(range);
		res = left_numbers[number_left] * right_numbers[number_right] + random(right_numbers[number_right]);
		game_answer= left_numbers[number_left];
		std::cout << res<< '/' << right_numbers[number_right] << '=' << std::endl;
		break;
	}
	cur_left = left_numbers[number_left];
	cur_right = right_numbers[number_right];
}
void GameSolveExamples::handle_player_answer()
{
	for (;;) {
		player_answer = WorkerWithStream::work_with_string(std::cin);
		if (player_answer == int(WorkerWithStream::answers::linefeed))
		{
			std::cout << "\n";
		}
		else if (player_answer == int(WorkerWithStream::answers::wrong_answer)||player_answer!=game_answer) {
			std::cout << "What?\n";
			handle_wrong_answer();
		}else
		{
			std::cout << "Right\n";
			++right_answers;
			return;
		}
	}
}
void GameSolveExamples::handle_wrong_answer()
{
	++wrong_answers;
	if (range >= MaxRange)	return;
	++range;
	left_numbers.push_back(cur_left);
	right_numbers.push_back(cur_right);
}
bool GameSolveExamples::check_answer()
{
	return  right_answers % 20;
	
}
GameSolveExamples::GameSolveExamples():wrong_answers(0),right_answers(0),start_game(time(NULL)){}
void GameSolveExamples::StartGame(const std::vector<char>& signs, const int original_range)
{
	range=original_range;
	if (range > MaxRange) {
		std::cout<<"Range is too large.\n";
		return;
	}
	
	fill_numbers();
	for(;;)
	{
		if (FlagSignal)
		{
			print_score();
			break;
		}
		create_example(signs,range);
		handle_player_answer();
		if (!check_answer())print_score();
	}
	
}
