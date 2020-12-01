#pragma once
#include <istream>
#include <vector>
#include "GameSolveExamples_.h"

class WrappingClass final
{
public:
	static bool start_use_game(std::istream& input, std::ostream& output, const std::vector<char>& _signs = Game::DefaultSigns, int original_range =Game:: DefaultRange);
};
