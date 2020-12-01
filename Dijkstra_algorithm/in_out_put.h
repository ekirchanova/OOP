#pragma once
#include <iostream>
#include <string>
#include<vector>
#include"Dijkstra_algorithm.h"
struct edge1 {
	std::string city_first;
	std::string city_second;
	int weight;
};
std::vector<weight_edge>  read(std::istream & input, std::string&source, std::vector <weight_edge>&graph);
void write_shortest_way(std::ostream &os, const std::vector<short_way>&shortest_way);