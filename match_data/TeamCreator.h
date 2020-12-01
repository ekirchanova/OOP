#pragma once
#include"creator.h"
class TeamCreator final :public Creator {
	enum class struct_team
	{
		team_id = 1,
		name,
		first_player_id,
		size=5
		
	};
public:
	std::shared_ptr<Product> create_product(const std::vector<std::string>& data)override;
};