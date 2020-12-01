#pragma once
#include"creator.h"
class PlayerCreator final:public Creator {
	enum class struct_player
	{
		player_id = 1,
		name,
		team_id,
		size = 4
	};
public:
	std::shared_ptr<Product>create_product(const std::vector<std::string>& data)override;
};