#include"PlayerCreator.h"
#include "processing_functions_of_string.h"
#include"Player.h"
namespace {
	bool check_error_during_create_player(id player_id, const std::string& name, id team_id) {
		return !player_id || !team_id || !name.size();
	}
	
}
std::shared_ptr<Product> PlayerCreator::create_product(const std::vector<std::string>& data) {
	if (data.size() != size_t(struct_player::size)) return nullptr;
	const id player_id = processing_functions_of_string::create_size_t(data[size_t(struct_player::player_id)]);
	const id team_id = processing_functions_of_string::create_size_t(data[size_t(struct_player::team_id)]);
	const std::string name = data[size_t(struct_player::name)];
	if (check_error_during_create_player(player_id, name, team_id))return  nullptr;
	std::shared_ptr<Player> new_player = std::make_shared<Player>(player_id, name, team_id);
	return new_player;
}
