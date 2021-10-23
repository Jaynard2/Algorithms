#pragma once
#include <vector>
#include <map>

struct Domain
{
	char kingdom;
	Domain* parent;
	unsigned rank;
};

class GalaxyMap
{
public:

	void create(unsigned x, unsigned y, unsigned z);
	void addKingdom(char id, const std::vector<int>& domains);
	void createSets();

private:
	unsigned _length;
	std::vector<std::vector<std::vector<Domain>>> _map;
	std::map<char, Domain*> _roots;


};

