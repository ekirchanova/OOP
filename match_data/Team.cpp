#include "Team.h"
#include"DataBase.h"
Team::~Team()
{
	DB->delete_team(team_id);
}

Team::Team(const id _id, const std::string& _team_name, const std::vector<id>& _players) :team_id(_id), team_name(_team_name), players_id(_players)
{
	DB->insert_team(_id,*this);
};
id Team::get_id()const noexcept {
	return team_id;
}
std::map<id, Player> Team::get_players()
{
	return DB->get_players();
};