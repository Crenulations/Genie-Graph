#pragma once
#include "Colony.h"
#include <random>
#include <functional>

class ColonyManager {
public:

	int max_nodes, max_edges;
	
	
	std::vector< Colony* > colonies;

	ColonyManager(int max_nodes, int max_edges);
	~ColonyManager();

	void CreateColony(std::vector< unsigned char > gene_buffer);

	std::vector< unsigned char > LoadGeneBuffer(const std::string& filepath);
	void SaveGeneBuffer(const std::string& filepath);
	std::vector< unsigned char > CreateRandomGeneBuffer();
	
};
