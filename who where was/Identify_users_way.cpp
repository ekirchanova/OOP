#include"Identify_users_way.h"
#include <iostream>
#include <utility>
#include <sstream>
#include <iterator>
#include<algorithm>
#include <cstdlib>
using namespace std;

void Identify_users_way::add_new_information_about_user(const userID new_user,const  time_place &new_information) {
		auto itMap=user_coordinates.find(new_user);
		if (itMap != user_coordinates.end()) {
			user_coordinates[new_user].insert(new_information);
		}
		else {
			map<time_t, coordinates,by_time>temp;
			temp.insert(new_information);
			user_coordinates.insert(make_pair(new_user, temp));
		}
}
Identify_users_way::Identify_users_way(const std::vector<std::pair<userID, time_place>>& users_way) {
	for (	auto&[user_ID, cur_place] : users_way) {
		if (user_ID == 0) continue;
		time_place temp = cur_place;
		add_new_information_about_user(user_ID,temp);
	}
}
void Identify_users_way::delete_user(const userID& user) {
	user_coordinates.erase(user);
}
map < userID, map<std::time_t, coordinates,by_time>> Identify_users_way::identify_way() const {
	if (!user_coordinates.size() )return map < userID, map<std::time_t, coordinates,by_time>>();
	return user_coordinates;
}
