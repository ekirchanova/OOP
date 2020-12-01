#pragma once
#include "match_data.h"
#include <string>

class Player final :public Product {
	id player_id;
	std::string player_name;
	id team_id;
public:
	Player() = default;
	~Player();
	Player(id _id, const std::string& _name, id _team);
	id get_id()const  noexcept override;
	Team& get_team();
};
