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
				_map[i][j][k].rank = 0;
			}
		}
	}

	_length = x * y * z;
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
	for (auto& i : _map)
	{
		for (auto& j : i)
		{
			for (auto& k : j)
			{
				const auto& root = _roots.find(k.kingdom);
				if (root == _roots.end())
				{
					_roots.insert(std::make_pair(k.kingdom, &k));
					k.parent = &k;
					k.rank = 0;
				}
				else
				{

				}
			}
		}
	}
}
