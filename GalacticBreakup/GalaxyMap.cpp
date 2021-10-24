#include "GalaxyMap.h"
#include <algorithm>
/*********************************************************
* Summary: Impl for GalaxyMap
*
* Author: Joshua Grieve
* Created: Oct 2021
*
* ©Copyright Cedarville University, its Computer Science faculty, and the
* authors. All rights reserved.
********************************************************/


void GalaxyMap::create(int x, int y, int z)
{
	_map.resize(x);
	for (int i = 0; i < x; i++)
	{
		_map[i].resize(y);
		for (int j = 0; j < y; j++)
		{
			_map[i][j].resize(z);
			for (int k = 0; k < z; k++)
			{
				_map[i][j][k].parent = &_map[i][j][k];
				_map[i][j][k].rank = 0;
			}
		}
	}
}

void GalaxyMap::reset()
{
	_map.clear();
	_kingdomRoots.clear();
	_empireRoots.clear();
}

void GalaxyMap::addKingdom(const std::vector<int>& domains)
{
	for (int i = 0; i < domains.size() - 1; i++)
	{
		//Math to calculate indexs from domain
		int x1 = domains[i] % _map.size();
		int y1 = (domains[i] / _map.size()) % _map[x1].size();
		int z1 = ((domains[i] / _map.size()) / _map[x1].size()) % _map[x1][y1].size();

		int x2 = domains[i + 1] % _map.size();
		int y2 = (domains[i + 1] / _map.size()) % _map[x2].size();
		int z2 = ((domains[i + 1] / _map.size()) / _map[x2].size()) % _map[x2][y2].size();

		combine(&_map[x1][y1][z1], &_map[x2][y2][z2]);
		
		
	}

	int x = domains[0] % _map.size();
	int y = (domains[0] / _map.size()) % _map[x].size();
	int z = ((domains[0] / _map.size()) / _map[x].size()) % _map[x][y].size();

	//Add kingdom sets to a list. This is helpful for creating the empire sets later
	DisjointNode* set = findSet(&_map[x][y][z]);
	if (std::find(_kingdomRoots.begin(), _kingdomRoots.end(), set) == _kingdomRoots.end())
	{
		_kingdomRoots.push_back(set);
	}
	
}

void GalaxyMap::createEmpireSets()
{
	//Doesn't actually delete the roots. This makes us "lose" them, so that we don't
	//have to check for duplicates
	_empireRoots.clear();

	for (int i = 0; i < _map.size(); i++)
	{
		for (int j = 0; j < _map[i].size(); j++)
		{
			for (int k = 0; k < _map[i][j].size(); k++)
			{
				DisjointNode* cur = findSet(&_map[i][j][k]);
				if (std::find(_kingdomRoots.begin(), _kingdomRoots.end(), cur) != _kingdomRoots.end())
				{
					//Do not process kingdom nodes
					continue;
				}

				if (i > 0)
				{
					DisjointNode* set = findSet(&_map[i - 1][j][k]);
					if (cur != set && std::find(_kingdomRoots.begin(), _kingdomRoots.end(), set) == _kingdomRoots.end())
					{
						combine(cur, set);
					}
				}
				if (i < _map.size() - 1)
				{
					DisjointNode* set = findSet(&_map[i + 1][j][k]);
					if (cur != set && std::find(_kingdomRoots.begin(), _kingdomRoots.end(), set) == _kingdomRoots.end())
					{
						combine(cur, set);
					}
				}

				if (j > 0)
				{
					DisjointNode* set = findSet(&_map[i][j - 1][k]);
					if (cur != set && std::find(_kingdomRoots.begin(), _kingdomRoots.end(), set) == _kingdomRoots.end())
					{
						combine(cur, set);
					}
				}
				if (j < _map[i].size() - 1)
				{
					DisjointNode* set = findSet(&_map[i][j + 1][k]);
					if (cur != set && std::find(_kingdomRoots.begin(), _kingdomRoots.end(), set) == _kingdomRoots.end())
					{
						combine(cur, set);
					}
				}

				if (k > 0)
				{
					DisjointNode* set = findSet(&_map[i][j][k - 1]);
					if (cur != set && std::find(_kingdomRoots.begin(), _kingdomRoots.end(), set) == _kingdomRoots.end())
					{
						combine(cur, set);
					}
				}
				if (k < _map[i][j].size() - 1)
				{
					DisjointNode* set = findSet(&_map[i][j][k + 1]);
					if (cur != set && std::find(_kingdomRoots.begin(), _kingdomRoots.end(), set) == _kingdomRoots.end())
					{
						combine(cur, set);
					}
				}

				cur = findSet(cur);
				if (std::find(_empireRoots.begin(), _empireRoots.end(), cur) == _empireRoots.end())
				{
					//Add roots to list so that they can be counted
					_empireRoots.push_back(cur);
				}
			}
		}
	}

	//Nodes that were roots may have become children
	_empireRoots.remove_if([](const auto* n) { return n != n->parent; });
}

bool GalaxyMap::empireConncted()const
{
	return _empireRoots.size() < 2;
}

void GalaxyMap::mergeKingdom(int domain)
{
	//Math to calculate indexs from domain
	int x = domain % _map.size();
	int y = (domain / _map.size()) % _map[x].size();
	int z = ((domain / _map.size()) / _map[x].size()) % _map[x][y].size();

	DisjointNode* set = findSet(&_map[x][y][z]);
	_kingdomRoots.remove_if([&](auto n) { return n == set; });

	//Recreate empire sets with new edges
	createEmpireSets();
	
}

void GalaxyMap::combine(DisjointNode* node1, DisjointNode* node2)
{
	link(findSet(node1), findSet(node2));
}

void GalaxyMap::link(DisjointNode* root1, DisjointNode* root2)
{
	if (root1->rank > root2->rank)
	{
		root1->parent = root2;
	}
	else
	{
		root2->parent = root1;
	}

	if (root1->rank == root2->rank)
	{
		root2->rank++;
	}
}

DisjointNode* GalaxyMap::findSet(DisjointNode* node)
{
	if (node != node->parent)
	{
		node->parent = findSet(node->parent);
	}

	return node->parent;
}
