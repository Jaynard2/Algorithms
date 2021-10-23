#pragma once
#include <vector>
#include <list>

struct Domain
{
	char kingdom;
	Domain* parent;
	int rank;
};

class GalaxyMap
{
public:

	void create(unsigned x, unsigned y, unsigned z);
	void reset();

	void addKingdom(char id, const std::vector<int>& domains);
	void createSets();

	unsigned countKingdomOccurences(char id) const;
	void mergeKingdoms(unsigned id1, unsigned id2);

private:
	unsigned _length;
	std::vector<std::vector<std::vector<Domain>>> _map;
	std::list<Domain*> _roots;


};

