#pragma once
#include <vector>

struct Domain
{
	char kingdom;
	Domain* parent;
};

class GalaxyMap
{
public:
	GalaxyMap(unsigned x, unsigned y, unsigned z);

private:
	std::vector<std::vector<std::vector<Domain>>> _map;
};

