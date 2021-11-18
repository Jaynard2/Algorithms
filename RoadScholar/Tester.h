#pragma once
#include <vector>
#include <string>
#include <queue>
#include "Intersection.h"
/*********************************************************
* Summary: Finds the distance along the shortest route using Dijkstra's
* algorithm
*
* Author: Nathanael Cook
* Created: Nov 2021
*
* ©Copyright Cedarville University, its Computer Science faculty, and the
* authors. All rights reserved.
********************************************************/

class Tester {
public:
	//Pass the number of Junktions in the Graph
	Tester(unsigned int numJunctions);
	~Tester();

	void addEdge(unsigned int x, unsigned int y, double weight);
	void addCity(unsigned char index, std::string Cty);

	//Pase the source node of the Graph
	bool test(unsigned char source, unsigned char source2, double distance);
	std::vector<std::pair<std::string, double>> getResult();

private:
	std::vector<std::vector<double>> _AdjMatrix;
	std::vector<std::pair<unsigned char, std::string>> _Cities;
	std::vector<Intersection> _Parents;
	//std::priority_queue<Intersection*, std::vector<Intersection*>, Intersection> _WorkingSet;
	std::vector<Intersection*> _WorkingSet;
	std::vector<std::pair<std::string, double>> _Result;

	bool walkParent(unsigned char index, unsigned char& source, unsigned char& source2);
	void clear();
	Intersection* sort(std::vector<Intersection*>::iterator begin, std::vector<Intersection*>::iterator end);
};