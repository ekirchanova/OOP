#pragma once
#include "match_data.h"
#include <string>
#include <vector>
#include<map>
class DataBase;
class Team final :public Product {
	id team_id;
	std::string team_name;
	std::vector< id> players_id;

public:
	Team() = default;
	~Team();
	Team(id _id, const std::string& _name_team, const std::vector<id>& _players);
	id get_id() const noexcept override;
	std::map<id, Player> get_players();

};
