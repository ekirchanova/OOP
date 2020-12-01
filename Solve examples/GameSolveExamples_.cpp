#include"GameSolveExamples_.h"
#include"Addition.h"
#include"Division.h"
#include"Multiplication.h"
#include"Substraction.h"
#include"WorkerWithStream.h"
#include <csignal>

namespace
{
	bool FlagSignal = false;
	const size_t CountRightAns = 20;
	std::map<char, std::unique_ptr<Operations>> create_operations_map(const std::vector<char>& signs)
	{
		std::map<char, std::unique_ptr<Operations>> operations_map;
		for (auto& sign : signs) {
			switch (sign) {
			case'+':
			default:
				operations_map.insert(std::make_pair('+', std::make_unique <Addition>()));
			case'-':
				operations_map.insert(std::make_pair('-', std::make_unique<Substraction>()));
			case'*':
				operations_map.insert(std::make_pair('*', std::make_unique<Multiplication>()));
			case'/':
				operations_map.insert(std::make_pair('/', std::make_unique<Division>()));
			}
		}
		return  operations_map;
	}
}
size_t Game::DefaultRange = 11;
std::vector<char>  Game::DefaultSigns = { '+','-','/','*' };
void Game::SignalHandler(int signum)
{
	FlagSignal = true;

}

void Game::print_score()
{
	std::vector<std::string> results=score_and_time.show_score();
	for(auto&it:results)
	{
		WorkerWithStream::write_in_stream(output, it);
	}
	
}

Operations* Game::random_sign()
{

	size_t number_sign=rand()%(signs.size()-1);
	return operations_map[signs[number_sign]].get();
}

bool Game::print_example(Operations* cur_operation)
{
	return WorkerWithStream::write_in_stream(output,cur_operation->show_example());
}

bool Game::get_and_check_answer(Operations*cur_operation)
{
	for (;;) {
		int answer = WorkerWithStream::set_answer(input);

		if (answer == int(WorkerWithStream::answers::bad_stream))return false;
		if (answer == int(WorkerWithStream::answers::linefeed))
		{
			WorkerWithStream::write_in_stream(output, "\n");
		}
		else if (answer == int(WorkerWithStream::answers::wrong_answer) || answer != cur_operation->get_right_answer()) {
			WorkerWithStream::write_in_stream(output, "What?\n");
			handle_wrong_answer(cur_operation);
			continue;
		}
		else
		{
			WorkerWithStream::write_in_stream(output, "Right\n");
			score_and_time.IncrementRightAnswers();
			return true;
		}
	}
}
void Game::handle_wrong_answer(Operations* cur_operation)
{
	score_and_time.IncrementWrongAnswers();
	numbers.add_left(cur_operation->get_left());
	numbers.add_right(cur_operation->get_right());
}
bool Game::check_count_right_answer()
{
	return score_and_time.get_count_right_answer()==CountRightAns;
}
Operations* Game::create_example()
{
	Operations* cur_operation = random_sign();
	int left = numbers.get_random_right();
	int right = numbers.get_random_right();
	cur_operation->create_example(left, right);
	return cur_operation;
}

Game::Game(const std::vector<char>& _signs, int original_range, std::istream& _input , std::ostream& _output ):numbers(original_range),
operations_map(create_operations_map(_signs)),signs(_signs),input(_input),output(_output)
{
	
}

Game::Game(std::istream& _input, std::ostream& _output, const std::vector<char>& _signs, int original_range): numbers(original_range),
operations_map(create_operations_map(_signs)),
 signs(_signs), input(_input), output(_output)
{
}

bool Game::start()
{
	if (signs.empty() || numbers.empty())return false;
	srand(time_t(0));
	signal(SIGINT, SignalHandler);
	for(;;)
	{
		if (FlagSignal)
		{
			print_score();
			break;
		}
		Operations * cur_operation=create_example();
		if(!print_example(cur_operation))
		{
			break;
		};
		if(!get_and_check_answer(cur_operation))
		{
			break;
		}
		if(check_count_right_answer()) print_score();
	}
	return true;
}


