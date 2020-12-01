#pragma once
#include"creator.h"
class MatchCreator final :public Creator {
	enum class struct_match
	{
		match_id = 1,
		first_team_id,
		second_team_id,
		time,
		location,
		first_team_point,
		second_team_point,
		first_player_id,
		size=8
	};
public:
	std::shared_ptr<Product> create_product(const std::vector<std::string>& data)override;
};
