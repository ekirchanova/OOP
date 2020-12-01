#include "DataBase.h"

#include <stdexcept>
namespace {
	bool check_player(const id player_id) {
		return !player_id;
	}
	bool check_team(const id team_id) {
		return !team_id;
	}
}
DataBase::DataBase(){}

std::map<id, Player> DataBase::get_players()
{
	return players;
}

void DataBase::clear()
{
	teams.erase(teams.begin(), teams.end());
	players.erase(players.begin(), players.end());
}

Player& DataBase::get_player(const id player_id)
{
	try {
		return players.at(player_id);
	}catch(...)
	{
		throw std::invalid_argument("don't exist player with  your id");
	}
}

std::map<id, Team> DataBase::get_teams()
{
	return teams;
}

Team& DataBase::get_team(const id team_id)
{

	try {
		return teams.at(team_id);
	}
	catch (...)
	{
		throw std::invalid_argument("don't exist team with  your id");
	}
}

void DataBase::insert_player(id player_id, const Player& new_player)
{
	if (check_player(player_id))return;
	players.insert(std::make_pair(player_id, std::ref(new_player)));
}

void DataBase::delete_player(const id player_id)
{
	auto it=players.find(player_id);
	if (it == players.end())return;
	players.erase(it);
}

void DataBase::insert_team( id team_id,const Team& new_team)
{
	if (check_player(team_id)) return;
	teams.insert(std::make_pair(team_id, std::ref(new_team)));
}

void DataBase::delete_team(const id team_id)
{
	auto it = teams.find(team_id);
	if (it == teams.end())return;
	teams.erase(it);
}
