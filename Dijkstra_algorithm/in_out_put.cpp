#include <iostream>
#include <utility>
#include <map>
#include <string>
#include<vector>
#include <sstream>
#include <iterator>
#include <cstdlib>
#include"Dijkstra_algorithm.h"
#include"in_out_put.h"
using namespace std;
namespace {
	const char SEPARATOR{ '-' };
	weight_edge create_new_edge(vector<string>&temp) {
		if (temp.size() != 3) return weight_edge();
		int weight;
		try {
			 weight = stoi(temp.at(2));
		}
		catch(...){
			return weight_edge();
		}
		return  make_pair(weight, make_pair(temp.at(0), temp.at(1)));
	}
	vector<weight_edge>read_graph(istream & input) {
		if (!input) return vector<weight_edge>();
		string str;
		vector<weight_edge> graph;
		while (getline(input, str)) {
			vector <string> temp;
			istringstream ist(str);
			copy(istream_iterator<string>(ist), {}, back_inserter(temp));
			graph.push_back(create_new_edge(temp));
			str.clear();
		}
		return graph;
	}
}
vector<weight_edge> read(istream & input,string&source) {
	if (!input) return vector<weight_edge>();
	string str;
	vector<string>temp;
	getline(input, str);
	istringstream ist(str);
	copy(istream_iterator<string>(ist), {}, back_inserter(temp));
	if (temp.size() == 2 && (temp[0].compare("s") == 0|| temp[0].compare("S") == 0)) {
		source = temp[1];
	}
	return read_graph(input);
}

void  write_shortest_way(ostream &os, const vector<short_way> &shortest_way) {
	if (!os) return;
	for (auto&[way, cities] :shortest_way ) {
		os << cities.at(cities.size() - 1);
		os << SEPARATOR<<'{';
		copy(cities.begin(),cities.end(), ostream_iterator<string>(os, ";"));
		os << '}' <<SEPARATOR<<way << endl;
	}
}