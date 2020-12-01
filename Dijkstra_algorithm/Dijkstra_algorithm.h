#pragma once
#include <string>
#include<vector>
typedef std::string vertex;
typedef std::pair<int, std::vector<vertex>> short_way;
typedef std::pair< vertex, vertex> edge;
typedef std::pair<int, edge>  weight_edge;
class Dijkstra_algorithm {
public:
	static std::vector<short_way> find_shortest_way(const std::vector<weight_edge>&graph, const vertex & vertex);
};

	
