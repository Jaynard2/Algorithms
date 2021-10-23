#pragma once
#include <vector>
#include <list>

struct DisjointNode
{
	unsigned rank;
	DisjointNode* parent;
};

class GalaxyMap
{
public:

	void create(int x, int y, int z);
	void reset();

	void addKingdom(const std::vector<int>& domains);
	void createEmpireSets();

	bool empireConncted() const;
	void mergeKingdom(int domain);

private:
	std::vector<std::vector<std::vector<DisjointNode>>> _map;
	std::list<DisjointNode*> _empireRoots;
	std::list<DisjointNode*> _kingdomRoots;

	void combine(DisjointNode* node1, DisjointNode* node2);
	void link(DisjointNode* root1, DisjointNode* root2);
	DisjointNode* findSet(DisjointNode* node);

};

