#include"Match.h"
#include"DataBase.h"
Match::Match(const id _match_id, const id _id1, const id _id2, const std::time_t _time, const std::string& _location, const std::pair<size_t, size_t>& _score, const std::vector<id>& _players) :
	match_id(_match_id), first_team_id(_id1), second_team_id(_id2), time(_time), location(_location), score(_score), players_id{ _players }{};
id Match::get_id() const noexcept {
	return match_id;
}
Team& Match::get_first_team()
{
	return DB->get_team(first_team_id);
}
Team& Match::get_second_team()
{
	return DB->get_team(second_team_id);
};
std::map<id, Player> Match::get_players()
{
	return DB->get_players();
};

