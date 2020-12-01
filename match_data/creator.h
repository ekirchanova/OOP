#pragma once
#include"match_data.h"
#include <vector>
#include <string>
#include <memory>
class TeamCreator;
class PlayerCreator;
class MatchCreator;
class Creator {
public:
	virtual ~Creator() = default;
	virtual std::shared_ptr <Product> create_product(const std::vector<std::string> &data) = 0;
};



