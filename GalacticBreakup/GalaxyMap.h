#pragma once
#include <vector>
#include <list>
/*********************************************************
* Summary: Declares the GalaxyMao, which manages all domains in the area
* and determines if the empire is continuous.
*
* Author: Joshua Grieve
* Created: Oct 2021
*
* ęCopyright Cedarville University, its Computer Science faculty, and the
* authors. All rights reserved.
********************************************************/

struct DisjointNode
{
	unsigned rank;
	DisjointNode* parent;
};

class GalaxyMap
{
public:
	//Initialize map with dimensions z, y, z
	void create(int x, int y, int z);
	void reset();

	//returns true if empire is continuous
	bool empireConncted() const;
	//Merges a kingdom set that contains the domain with an empire set
	void mergeKingdom(const std::vector<int>& domains);

private:
	std::vector<std::vector<std::vector<DisjointNode>>> _map;
	std::list<DisjointNode*> _empireRoots;

	//Makes any set that is not a kingdom an empire set
	void createEmpireSets();

	void combine(DisjointNode* node1, DisjointNode* node2);
	void link(DisjointNode* root1, DisjointNode* root2);
	DisjointNode* findSet(DisjointNode* node);

};

