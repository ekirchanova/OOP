#include <iostream>
#include <utility>
#include <string>
#include<vector>
#include <sstream>
#include <iterator>
#include<algorithm>
#include <cstdlib>
#include "Dijkstra_algorithm.h"
using namespace std;
namespace {
	bool  cheak_visiting(const vertex &current_vertex, const vector<vertex>& visited_vertexs) {
		auto result = find(visited_vertexs.begin(), visited_vertexs.end(), current_vertex);
		if (result != visited_vertexs.end()) return true;
		else return false;
	}
	bool check_name(const vertex&name_vertex, const edge& current_vertex) {
		return  (name_vertex == current_vertex.first || name_vertex == current_vertex.second);
	}
	bool compare(weight_edge&a, weight_edge&b) {
		return a.first < b.first;
	}

	bool  check_weight(const vector<weight_edge>&graph) {
		vector<weight_edge> graph_edge = graph;
		sort(graph_edge.begin(), graph_edge.end(), compare);
		if (graph_edge[0].first < 0) return false;
		return true;
	}
	void find_way(const vector<weight_edge>&graph_edge, vector<short_way>&shortest_current_way, const vector<vertex> & currrent_distance, const vertex& name_vertex, const size_t min_way) {
		shortest_current_way.clear();
		size_t min = 0;
		vector<vertex> temp_vertexs;
		size_t current_way;
		for (auto&[way, city]: graph_edge) {
			if (check_name(name_vertex, city)) {
				temp_vertexs = currrent_distance;
				current_way = way + min_way;
				if (name_vertex == city.first) {
					temp_vertexs.push_back(city.second);
				}
				else {
					temp_vertexs.push_back(city.first);
				}
				shortest_current_way.push_back(make_pair(current_way, temp_vertexs));
			}
		}
	}
	bool find_nearest_vertex(const vector<short_way>&shortest_way, const vector<vertex>& visited_vertexs, vertex&nearest_vertex, size_t& min_way, vector<vertex> &nearest_distance) {
		min_way = numeric_limits<int>::max();
		nearest_distance.clear();
		bool find_nearest_vertex = false;
		for (auto& [way,cities] : shortest_way) {
			vertex current_vertex = cities.at(cities.size() - 1);
			if (cheak_visiting(current_vertex, visited_vertexs)) continue;
			if (min_way > way) {
				min_way = way;
				nearest_distance =cities;
				nearest_vertex = current_vertex;
				find_nearest_vertex = true;
			}
		}
		return find_nearest_vertex;
	}
	size_t find_vertex(const vector<short_way>&shortest_way, const vertex&current_vertex) {
		for (size_t i = 0; i < shortest_way.size(); i++)
		{
			vertex needed_vertex = shortest_way[i].second.at(shortest_way[i].second.size() - 1);
			if (current_vertex == needed_vertex)
				return i;
		}
		return shortest_way.size();
	}
	void compare_distance(vector<short_way>&shortest_way, const vector< short_way> &shortest_current_way, const vertex&source) {
		for (auto&[way, cities]: shortest_current_way)
		{
			vertex current_vertex = cities.at(cities.size() - 1);
			if (current_vertex == source)continue;
			size_t number = find_vertex(shortest_way, current_vertex);
			if (number == shortest_way.size()) {
				shortest_way.push_back({ way, cities });
			}
			else {
				if (way < shortest_way[number].first)
					shortest_way[number] = { way, cities };
			}
		}
	}
	
}
vector<short_way> Dijkstra_algorithm:: find_shortest_way(const vector<weight_edge>&graph, const vertex & source) {
	if (graph.size() == 0 || source.size() == 0)return vector<short_way>();
	if (!check_weight(graph)) return vector<short_way>();
	vector<vertex> visited_vertexs, current_distance;
	vector<short_way>shortest_way;
	vertex nearest_vertex;
	size_t min_way=0;
	visited_vertexs.push_back(source);
	vector< short_way>shortest_current_way;
	current_distance.push_back(source);
	find_way(graph,shortest_way,current_distance, source, 0);
	while(find_nearest_vertex(shortest_way,visited_vertexs, nearest_vertex, min_way, current_distance)){
		find_way(graph,shortest_current_way, current_distance, nearest_vertex,min_way);
		compare_distance(shortest_way,shortest_current_way,source);
		visited_vertexs.push_back(nearest_vertex);
	}
	return shortest_way;
}
