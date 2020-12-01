#pragma once
#include <iostream>
#include <string>
#include<vector>
#include<map>
#include <ctime>
typedef std::size_t userID;
typedef std::pair<int, int>coordinates;
typedef std::pair<std::time_t, coordinates > time_place;
struct by_time {
	bool  operator()( const std::time_t&a, const std::time_t&b) const {
		return difftime(a, b) < 0.0;
	}
};
class Identify_users_way {
	std::map<userID, std::map<std::time_t, coordinates,by_time>> user_coordinates;
public:
	Identify_users_way()=default;
	Identify_users_way(const std::vector<std::pair<userID, time_place>>& users_way);
	~Identify_users_way() = default;

	void add_new_information_about_user(const userID new_user, const time_place &new_information);
	void delete_user(const userID& user);
	std::map < userID, std::map<std::time_t, coordinates,by_time>> identify_way() const;
};
