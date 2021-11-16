#pragma once
#include <vector>
#include <string>
#include <queue>
#include "Intersection.h"

class Tester {
public:
	//Pass the number of Junktions in the Graph
	Tester(unsigned int numJunctions);
	~Tester();

	void addEdge(unsigned int x, unsigned int y, float weight);
	void addCity(unsigned char index, std::string Cty);

	//Pase the source node of the Graph
	bool test(unsigned char source, unsigned char source2, float distance);
	std::vector<std::string> getResult();

private:
	std::vector<std::vector<float>> _AdjMatrix;
	std::vector<std::pair<unsigned char, std::string>> _Cities;
	std::vector<Intersection*> _Parents;
	std::priority_queue<Intersection*, std::vector<Intersection*>, Intersection> _WorkingSet;
	std::vector<std::string> _Result;

	bool walkParent(unsigned char index, unsigned char& source, unsigned char& source2);
	void clear();
};