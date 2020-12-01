#include"MatchCreator.h"
#include"Match.h"
#include "processing_functions_of_string.h"
namespace {
	bool  check_error_id_during_create_match(id match_id, id first_team_id, id second_team_id, const std::vector<id>& players_id) {
		return !match_id || !first_team_id || !second_team_id || !players_id.size();
	}
	bool  check_error_during_create_match(const std::string& location, const std::time_t& match_time) {
		return !location.size() || match_time == -1 || match_time == time_t();
	}
}
std::shared_ptr<Product> MatchCreator::create_product(const std::vector<std::string>& data) {
	if (data.size() < size_t(struct_match::size)) return nullptr;
	const id match_id = processing_functions_of_string::create_size_t(data[size_t(struct_match::match_id)]);
	const id  first_team_id = processing_functions_of_string::create_size_t(data[size_t(struct_match::first_team_id)]);
	const id second_team_id = processing_functions_of_string::create_size_t(data[size_t(struct_match::second_team_id)]);
	const std::time_t match_time = processing_functions_of_string::create_time(data[size_t(struct_match::time)]);
	const std::string location = data[size_t(struct_match::location)];
	const size_t first_team_point = processing_functions_of_string::create_size_t(data[size_t(struct_match::first_team_point)]);
	const size_t second_team_point = processing_functions_of_string::create_size_t(data[size_t(struct_match::second_team_point)]);
	const std::pair<size_t, size_t> score = std::make_pair(first_team_point, second_team_point);
	const std::vector<id> players = processing_functions_of_string::create_numbers(data, size_t(struct_match::first_player_id));
	if (check_error_id_during_create_match(match_id, first_team_id, second_team_id, players) ||
		check_error_during_create_match(location, match_time)) return  nullptr;
	return std::make_shared<Match>(match_id, first_team_id, second_team_id, match_time, location, score, players);
}
