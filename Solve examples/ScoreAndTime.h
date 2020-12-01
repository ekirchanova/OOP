#pragma once
#include <ctime>
#include <string>
#include <vector>

class ScoreAndTime final
{
    size_t wrong_answers;
    size_t right_answers;
    time_t start_game, start_print_score;
    void stop_game();
    void continue_game();
    size_t calculate_score();
    time_t calculate_seconds_per_problem();
public:
    ScoreAndTime();
    void IncrementRightAnswers();
    void IncrementWrongAnswers();
    std::vector<std::string> show_score();
    size_t get_count_right_answer();
};
