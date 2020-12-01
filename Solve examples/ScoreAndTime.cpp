#include "ScoreAndTime.h"
#include<sstream>
namespace
{
	const size_t PER_CENTS = 100;
}
void ScoreAndTime::stop_game()
{
	start_print_score =time_t(0);
}
void ScoreAndTime::continue_game()
{
	time_t end_print_game=time_t(0);
	start_game += end_print_game - start_print_score;
}
ScoreAndTime::ScoreAndTime():right_answers(0),wrong_answers(0),start_game(time(0))
{
}
void ScoreAndTime::IncrementRightAnswers()
{
	++right_answers;
}
void ScoreAndTime::IncrementWrongAnswers()
{
	++wrong_answers;
}
size_t ScoreAndTime::calculate_score()
{
	return (right_answers *PER_CENTS) / (right_answers + wrong_answers);
}
time_t ScoreAndTime::calculate_seconds_per_problem()
{
	return start_print_score - start_game / (right_answers );
}
std::vector<std::string> ScoreAndTime::show_score()
{
	stop_game();
	std::vector<std::string> result;
	std::ostringstream output_score,output_time;
	output_score << "\nRight " << right_answers << " ;Wrong " << wrong_answers << "Score " << calculate_score() << "%";
	result.push_back(output_score.str());
	if (right_answers == 0) return result;
	output_time<< "Total time " << start_print_score - start_game << " seconds;";
	output_time << calculate_seconds_per_problem() << " seconds per problem ";
	result.push_back(output_time.str());
	return result;
}

size_t ScoreAndTime::get_count_right_answer()
{
	return right_answers;
}
