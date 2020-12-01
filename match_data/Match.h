#pragma once
#include "match_data.h"
#include <vector>
#include <string>
#include <ctime>
#include<map>
class Match final :public Product {
	id match_id;
	id first_team_id, second_team_id;
	std::time_t time;
	std::string location;
	std::pair<size_t, size_t> score;
	std::vector<id> players_id;
public:
	Match(id _match_id, id _id1, id _id2, std::time_t _time, const std::string& _location, const std::pair<size_t, size_t>& _score, const std::vector<id>& _players);
	id get_id()const noexcept override;
	Team& get_first_team();
	Team& get_second_team();
	std::map<id, Player> get_players();
};
