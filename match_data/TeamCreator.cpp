#include "TeamCreator.h"
#include "Team.h"
#include "processing_functions_of_string.h"

namespace {
	bool  check_error_during_create_team(id team_id, const std::string& name, const std::vector<id>& players_id) {
		return !team_id || !name.size() || !players_id.size();
	}
}
std::shared_ptr<Product> TeamCreator::create_product(const std::vector<std::string>& data) {
	if (data.size() < size_t(struct_team::size)) return nullptr;
	const id team_id = processing_functions_of_string::create_size_t(data[size_t(struct_team::team_id)]);
	const std::string name = data[size_t(struct_team::name)];
	const std::vector<id> players = processing_functions_of_string::create_numbers(data, size_t(struct_team::first_player_id));
	if (check_error_during_create_team(team_id, name, players))return nullptr;
	std::shared_ptr<Team> new_team = std::make_shared<Team>(team_id, name, players);
	return new_team;
}