#pragma once
#include <vector>
#include <string>
#include <queue>

class Intersection {
public:
	Intersection(unsigned int x, unsigned char y, unsigned char z) {
		distance = x;
		id = y;
		parent = z;
	}

	float distance;
	unsigned char id;
	unsigned char parent;

	bool operator<(Intersection val) {
		return distance < val.distance;
	}
	bool operator>(Intersection val) {
		return distance > val.distance;
	}
};

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
	std::priority_queue<Intersection*> _WorkingSet;
	std::vector<std::string> _Result;

	bool walkParent(unsigned char index, unsigned char source2);
};