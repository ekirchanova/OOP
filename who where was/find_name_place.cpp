#include"find_name_place.h"
#include <iostream>
#include <utility>
#include <string>
#include<vector>
#include <sstream>
#include <iterator>
#include<algorithm>
#include <cstdlib>

using namespace std;
namespace {
	const string UNKNOWN_PLACE = "unknown_place";
	bool cmp_1(const pair<Region, name_place>& a, const Region &b)  {
		return a.first.cur_region.second < b.cur_region.second;
	}
	bool cmp_2(const Region &b,const pair<Region, name_place>& a) {
		return a.first.cur_region.first > b.cur_region.first ;
	}

}
vector<name_place> name_places::find_name_place(const coordinates& cur_coordinates) const  {
	vector<name_place> cur_name;
	Region cur;
	const region temp_reg= make_pair(cur_coordinates, cur_coordinates);
	cur.cur_region = temp_reg;
	const auto first= lower_bound(place_coordinates.begin(), place_coordinates.end() ,cur,cmp_1);
	const auto last = upper_bound(place_coordinates.begin(), place_coordinates.end(), cur, cmp_2);
	for (auto it = first; it != last; ++it)
	{
		const auto&[first_coord, second_coord] = it->first.cur_region;
		if ((cur_coordinates >= first_coord) && (cur_coordinates <= second_coord))
			cur_name.push_back(it->second);
	}
	if (cur_name.size() == 0)
		cur_name.push_back(UNKNOWN_PLACE);
	return cur_name;
}
name_places::name_places(const std::vector<coordinates_place>&_place_coordinates) {
	for (auto&it : _place_coordinates) {
		Region cur;
		if (it.first_coordinates<it.second_coordinates) {
			cur.cur_region=make_pair(it.first_coordinates, it.second_coordinates);
		}
		else {
			cur.cur_region=make_pair(it.second_coordinates, it.first_coordinates);
		}
		place_coordinates.insert(make_pair(cur, it.name));
	}
}
void name_places::add_new_place(const Region& new_region, const name_place& name)
{	
	place_coordinates.insert(make_pair(new_region, name));
}
void name_places:: delete_region(const Region& d_region) {
	place_coordinates.erase(d_region);
}
map<userID, route> name_places::identify_name_place( const Identify_users_way& user_coordinates)const  {
	map<userID, route>  users_way;
	for (const auto&[user_ID, cur_route] : user_coordinates.identify_way()) {
		route current_users_way;
		for (auto&timeplace : cur_route) {
			current_users_way.push_back(make_pair(timeplace, find_name_place(timeplace.second)));
		}
		users_way.insert(make_pair(user_ID, current_users_way));
	}
	return users_way;
}