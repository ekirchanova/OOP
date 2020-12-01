#pragma once
#include"Identify_users_way.h"
#include"find_name_place.h"
#include <iostream>
#include <string>
#include<vector>
namespace work_with_streams {
	static std::vector<std::pair<userID, time_place>> read_about_users(std::istream & input);
	static std::vector< coordinates_place> read_about_places(std::istream & input);
	static void print_way_to_file(const std::map<userID, route>&users_way);
};