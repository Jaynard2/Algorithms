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
				_map[i][j][k].parent = nullptr;
			}
		}
	}
}

void GalaxyMap::reset()
{
	_map.clear();
	_empireRoots.clear();
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
				if (_map[i][j][k].parent == nullptr)
				{
					//Do not process kingdom nodes
					continue;
				}

				auto cur = findSet(&_map[i][j][k]);

				if (i > 0)
				{
					if ( _map[i - 1][j][k].parent != nullptr && cur != findSet(&_map[i - 1][j][k]))
					{
						combine(cur, &_map[i - 1][j][k]);
						cur = findSet(&_map[i][j][k]);
					}
				}
				if (i < _map.size() - 1)
				{
					if (_map[i + 1][j][k].parent != nullptr && cur != findSet(&_map[i + 1][j][k]))
					{
						combine(cur, &_map[i + 1][j][k]);
						cur = findSet(&_map[i][j][k]);
					}
				}

				if (j > 0)
				{
					if (_map[i][j - 1][k].parent != nullptr && cur != findSet(&_map[i][j - 1][k]))
					{
						combine(cur, &_map[i][j - 1][k]);
						cur = findSet(&_map[i][j][k]);
					}
				}
				if (j < _map[i].size() - 1)
				{
					if (_map[i][j + 1][k].parent != nullptr && cur != findSet(&_map[i][j + 1][k]))
					{
						combine(cur, &_map[i][j + 1][k]);
						cur = findSet(&_map[i][j][k]);
					}
				}

				if (k > 0)
				{
					if (_map[i][j][k - 1].parent != nullptr && cur != findSet(&_map[i][j][k - 1]))
					{
						combine(cur, &_map[i][j][k - 1]);
						cur = findSet(&_map[i][j][k]);
					}
				}
				if (k < _map[i][j].size() - 1)
				{
					if (_map[i][j][k + 1].parent != nullptr && cur != findSet(&_map[i][j][k + 1]))
					{
						combine(cur, &_map[i][j][k + 1]);
						cur = findSet(&_map[i][j][k]);
					}
				}

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

void GalaxyMap::mergeKingdom(const std::vector<int>& domains)
{
	for (const auto& i : domains)
	{
		int x = i % _map.size();
		int y = (i / _map.size()) % _map[x].size();
		int z = (i / _map.size() / _map[x].size()) % _map[x][y].size();

		auto& n = _map[x][y][z];
		n.rank = 0;
		n.parent = &n;
	}

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
