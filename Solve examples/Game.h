#pragma once
#include<vector>
const size_t  DefaultRange = 11;
const std::vector<char>  DefaultSigns = { '+','-' };
const size_t MaxRange = 100;
const size_t NeededCountRightAns = 20;
 class GameSolveExamples final
 {
    
     size_t game_answer;
     size_t cur_left, cur_right;
     int player_answer;
     size_t range;
     std::vector<size_t> right_numbers;
     std::vector<size_t> left_numbers;
 	
     void print_score();
     size_t calculate_score();
     time_t calculate_seconds_per_problem(const time_t &end);
     size_t game_rand(size_t cur_range);
     size_t random(size_t cur_range);
     static void SignalHandler(int signum);
     void fill_numbers();
     void create_example(const std::vector<char>& signs, int range);
     void handle_player_answer();
     void handle_wrong_answer();
     bool check_answer();
 public:
     GameSolveExamples();
     void StartGame(const std::vector<char> &signs=DefaultSigns ,int original_range =DefaultRange);
 };