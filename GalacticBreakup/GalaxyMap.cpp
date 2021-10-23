#include "GalaxyMap.h"
#include <exception>

void GalaxyMap::create(unsigned x, unsigned y, unsigned z)
{
	_map.resize(x);
	for (unsigned i = 0; i < x; i++)
	{
		_map[i].resize(y);
		for (unsigned j = 0; j < y; j++)
		{
			_map[i][j].resize(z);
			for (unsigned k = 0; k < z; k++)
			{
				_map[i][j][k].kingdom = 0;
				_map[i][j][k].parent = &_map[i][j][k];
				_map[i][j][k].rank = -1;
			}
		}
	}

	_length = x * y * z;
}

void GalaxyMap::reset()
{
	_map.clear();
	_length = 0;
	_roots.clear();
}

void GalaxyMap::addKingdom(char id, const std::vector<int>& domains)
{
	for (const auto& i : domains)
	{
		if (i >= _length)
			throw std::exception("Domain ID to big");

		int x = i % _map.size();
		int y = (i / _map.size()) % _map[0].size();
		int z = (i / (_map.size() * _map[0].size()));

		_map[x][y][z].kingdom = id;
	}
}

void GalaxyMap::createSets()
{
	for (unsigned x = 0; x < _map.size(); x++)
	{
		for (unsigned y = 0; y < _map[x].size(); y++)
		{
			for (unsigned z = 0; z < _map[x][y].size(); z++)
			{
				if (x > 0 && _map[x][y][z].kingdom == _map[x - 1][y][z].kingdom)
				{
					_map[x][y][z].parent = &_map[x - 1][y][z];
					_map[x][y][z].rank = _map[x - 1][y][z].rank + 1;
				}
				else if (y > 0 && _map[x][y][z].kingdom == _map[x][y - 1][z].kingdom)
				{
					_map[x][y][z].parent = &_map[x][y - 1][z];
					_map[x][y][z].rank = _map[x][y - 1][z].rank + 1;
				}
				else if (z > 0 && _map[x][y][z].kingdom == _map[x][y][z - 1].kingdom)
				{
					_map[x][y][z].parent = &_map[x][y][z  -1];
					_map[x][y][z].rank = _map[x][y][z - 1].rank + 1;
				}
				else
				{
					_map[x][y][z].parent = &_map[x][y][z];
					_map[x][y][z].rank = 0;

					_roots.push_back(&_map[x][y][z]);
				}
			}
		}
	}
}

unsigned GalaxyMap::countKingdomSplits(char id) const
{
	int count = 0;
	for (const auto& i : _roots)
	{
		if (i->kingdom == id)
			count++;
	}

	return count;
}

void GalaxyMap::mergeKingdoms(unsigned id1, unsigned id2)
{
	if (id1 >= _length)
		throw std::exception("ID1 to big");

	int x1 = id1 % _map.size();
	int y1 = (id1 / _map.size()) % _map[0].size();
	int z1 = (id1 / (_map.size() * _map[0].size()));

	if (id2 >= _length)
		throw std::exception("ID2 to big");

	int x2 = id2 % _map.size();
	int y2 = (id2 / _map.size()) % _map[0].size();
	int z2 = (id2 / (_map.size() * _map[0].size()));

	Domain* node1= &_map[x2][y2][z2];

	while (node1!= node1->parent)
	{
		node1 = node1->parent;
	}

	_roots.remove(node1);
	node1->parent = &_map[x1][y1][z1];
	
}
