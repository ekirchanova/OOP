#include"in_out_put.h"
#include <sstream>
#include <iterator>
#include <cstdlib>
#include <iomanip>
#include <time.h>
#include<fstream>
using namespace std;
using namespace work_with_streams;
namespace {
	const size_t SIZE_ARG_USER_INF= 4;
	const size_t SIZE_ARG_PLACE_INF =5 ;
	time_t create_time(const string&cur_str) {
		tm time = {};
		istringstream in(cur_str);
		in >> get_time(&time, "%Y-%m-%dT%X");
		return mktime(&time);
	}
	vector<int> create_vector_coordinates(const vector<string>&cur_str, size_t number) {
		vector<int> numbers;
		for (size_t i = number; i <cur_str.size(); i++) {
			try {
				numbers.push_back(stoi(cur_str.at(i)));
			}
			catch (...) {
				continue;
			}
		}
		return numbers;
	}
	pair< userID, time_place> create_new_information_about_user(const vector<string>&cur_str) {
		if (cur_str.size()< SIZE_ARG_USER_INF) return pair< userID, time_place>();
		size_t id;
		try {
			id =stoi(cur_str.at(0));
		}
		catch (...) {
			return pair< userID, time_place>();
		}
		vector<int> numbers = create_vector_coordinates(cur_str, 2);
		if (numbers.size() != SIZE_ARG_USER_INF-2) return pair< userID, time_place>();
		coordinates current_coordinates = make_pair(numbers.at(0), numbers.at(1));
		return make_pair(id, make_pair(create_time(cur_str.at(1)), current_coordinates));
	}
	 coordinates_place create_new_information_about_place(const vector<string>&cur_str) {
		 coordinates_place cur;
		 if (cur_str.size() < SIZE_ARG_PLACE_INF) return coordinates_place();
		 vector<int> numbers = create_vector_coordinates(cur_str, 1);
		 if (numbers.size() != SIZE_ARG_PLACE_INF-1) return coordinates_place();
		 coordinates first_coordinates = make_pair(numbers.at(0), numbers.at(1));
		 coordinates second_coordinates = make_pair(numbers.at(2), numbers.at(3));
		 cur.name=cur_str.at(0);
		 cur.first_coordinates =first_coordinates;
		 cur.second_coordinates =second_coordinates;
		 return cur;
	}
	 void print_full_way_current_user(ofstream&fout, const route &way) {
		 fout << "Full way:" << endl;
		 for (const auto&[time_coord, name] : way) {
			 fout <<"->";
			 fout << "{ ";
			 copy(name.begin(), name.end(), ostream_iterator<string>(fout, "; "));
			 fout << "} ";
		 }
	 }
	 void print_way_current_user(ofstream&fout, const route& way) {
		 for (const auto&[time_coord, name] : way) {
			 const auto&[time, coord] = time_coord;
			 const auto&[x, y] = coord;
			 tm cur_str_time;
			 localtime_s(&cur_str_time, &time);
			 fout<< put_time(&cur_str_time, "%Y-%m-%dT%X");
			 fout << " (" << x << "," << y << ") ";
			 copy(name.begin(), name.end(), ostream_iterator<string>(fout, "; "));
			 fout << endl;
		 }
	 }
}
std::vector<std::pair<userID, time_place>> work_with_streams::read_about_users(istream & input) {
	if (!input) return std::vector<std::pair<userID, time_place>>();
	std::vector<std::pair<userID, time_place>>current_users;
	for (string str; getline(input, str);) {
		vector <string>cur_str;
		istringstream ist(str);
		copy(istream_iterator<string>(ist), {}, back_inserter(cur_str));
		try {
			current_users.push_back(create_new_information_about_user(cur_str));
		}
		catch (...) {
			continue;
		}
	}
	return current_users;
}
vector< coordinates_place> work_with_streams::read_about_places(istream & input) {
	if (!input) return vector< coordinates_place>();
	vector< coordinates_place> places;
	for (string str; getline(input, str);) {
		vector <string>cur_str;
		istringstream ist(str);
		copy(istream_iterator<string>(ist), {}, back_inserter(cur_str));
		places.push_back(create_new_information_about_place(cur_str));
	}
	return places;
}
void work_with_streams::print_way_to_file(const map<userID, route>&users_way) {
	for (const auto&[user_ID, way] : users_way) {
		ostringstream oss;
		oss << (size_t)user_ID;
		ofstream fout(oss.str());
		fout << user_ID << endl;
		print_way_current_user(fout, way);
		print_full_way_current_user(fout, way);
		fout.close();
	}
}