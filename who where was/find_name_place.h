#pragma once
#include"Identify_users_way.h"
typedef std::string name_place;
typedef std::pair< coordinates, coordinates> region;
typedef std::vector<std::pair<time_place, std::vector<name_place>>> route;
typedef struct coordinates_place {
	name_place name;
	coordinates first_coordinates, second_coordinates;
}coordinates_place;
struct by_coordinates {
	bool operator()(const coordinates&a,const  coordinates&b) const  {
		return a.first< b.first ||a.second < b.second;
	};
};
struct Region {
	region cur_region;
	bool operator < (const Region&b)const {
		if (cur_region.first != b.cur_region.first)
			return cur_region.first < b.cur_region.first;
		else 
			return cur_region.second < b.cur_region.second;
	};
};
class name_places {
	std::map<Region,name_place> place_coordinates;
	std::vector<name_place> find_name_place(const coordinates& cur_coordinates) const;
public:
	name_places() = default;
	name_places(const std::vector<coordinates_place>&_place_coordinates);
	~name_places() = default;
	void delete_region(const Region& d_region);
	void add_new_place(const Region &new_region, const name_place& name);
	std::map<userID, route> identify_name_place(const Identify_users_way &user_coordinates) const;
};