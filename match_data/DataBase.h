#pragma once
#include<map>
#include"Player.h"
#include"Team.h"
class DataBase final {
private:
	std::map<id, Team > teams;
	std::map<id, Player> players;
public:
	DataBase();
	void clear();
	Player& get_player(id player_id);
	std::map<id, Player> get_players();

	std::map<id, Team> get_teams();
	Team& get_team(id team_id);

	void insert_player(id player_id,const Player& new_player);
	void delete_player(id player_id);

	void insert_team(id team_id,const Team& new_team);
	void delete_team(id team_id);
};