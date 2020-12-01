#include "AdaptClass.h"
bool WrappingClass::start_use_game(std::istream& input, std::ostream& output, const std::vector<char>& _signs, int original_range )
{
	Game solution(_signs,original_range,input, output);
	return solution.start();
}
