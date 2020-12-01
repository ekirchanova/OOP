#include "Player.h"
#include"DataBase.h"
Player::~Player()
{
	DB->delete_player(player_id);
}

Player::Player(const id _id, const std::string& _player_name, id _team) :player_id(_id), player_name(_player_name), team_id(_team)
{
	DB->insert_player(_id,*this);
}
id Player::get_id()const  noexcept {
	return player_id;
}
Team& Player::get_team()
{
	return DB->get_team(team_id);
}