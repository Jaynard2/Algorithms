#include "Tester.h"
#include <tuple>
#include <algorithm>
#include <cmath>
/*********************************************************
* Summary: Implemets the Test class.
*
* Author: Nathanael Cook
* Created: Nov 2021
*
* ©Copyright Cedarville University, its Computer Science faculty, and the
* authors. All rights reserved.
********************************************************/

Tester::Tester(unsigned int numJunctions) {
	//Inistalilze the adjacentcy Matrix
	_AdjMatrix.resize(numJunctions);
	for (int i = 0; i < numJunctions; i++) {
		_AdjMatrix.at(i).resize(numJunctions, -1.0f);
	}

	_Parents.reserve(numJunctions);
}

Tester::~Tester() {
	clear();
}

void Tester::clear() {
	Intersection* temp = nullptr;
	while (_Parents.size() > 0) {
		temp = _Parents.back();
		_Parents.pop_back();
		delete temp;
		temp = nullptr;
	}
	_Result.clear();
}

void Tester::addEdge(unsigned int node1, unsigned int node2, float weight) {
	_AdjMatrix.at(node1).at(node2) = weight;
	_AdjMatrix.at(node2).at(node1) = weight;
}

void Tester::addCity(unsigned char index, std::string Cty) {
	_Cities.push_back(std::pair<unsigned char, std::string>(index, Cty));
}

bool Tester::test(unsigned char source, unsigned char source2, float distance) {
	//Initalize Data class
	clear();
	Intersection* temp = nullptr;
	for (int i = 0; i < _AdjMatrix.size(); i++) {
		//set all distances and parents to int Max except the source so it will be at the top of the queue
		if (i == source) {
			temp = new Intersection(0, source, source);
		}
		else {
			temp = new Intersection(INT_MAX, i, CHAR_MAX);
		}
		//after creation add to the queue and the parent vector, this make for easy lookup and
		//parent will hold the finished Results
		_WorkingSet.push(temp);
		_Parents.push_back(temp);
		temp = nullptr;
	}

	std::vector<float> edges;
	float newDistance = 0.0f;
	Intersection* neighbor;
	while (!_WorkingSet.empty()) {
		//Force a resort
		temp = _WorkingSet.top();
		_WorkingSet.pop();
		_WorkingSet.push(temp);

		temp = _WorkingSet.top();
		_WorkingSet.pop();

		edges = _AdjMatrix.at(temp->id);
		for (int i = 0; i < edges.size(); i++) {
			if (edges.at(i) < 0) {
				continue;
			}

			newDistance = temp->distance + edges.at(i);
			neighbor = _Parents.at(i);
			if (newDistance < neighbor->distance) {
				neighbor->distance = newDistance;
				neighbor->parent = temp->id;
			}
		}
	}

	for (auto obj : _Cities) {
		if (walkParent(obj.first, source, source2)) {
			_Result.push_back(std::make_pair(obj.second, roundf(_Parents.at(obj.first)->distance - distance)));
		}

		std::sort(_Result.begin(), _Result.end(), [](const auto& a, const auto& b)
			{
				//Sort by distance
				if (a.second < b.second)
				{
					return true;
				}
				else if (a.second > b.second)
				{
					return false;
				}

				//Sort alpha if distance the same
				unsigned i = 0;
				while (i < a.first.length() && i < b.first.length())
				{
					if (a.first[i] < b.first[i])
					{
						return true;
					}
					else if (a.first[i] < b.first[i])
					{
						return false;
					}
				}

				return a.first.length() < b.first.length();
			});
	}

	return true;
}

bool Tester::walkParent(unsigned char index, unsigned char& source, unsigned char& source2) {
	if (index == source2) {
		//base case
		auto nextNode = _Parents.at(_Parents.at(index)->parent);
		//source parent is set to itsself
		if (nextNode->parent == source) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (index == source) {
		return false;
	}
	return walkParent(_Parents.at(index)->parent, source, source2);
}

std::vector<std::pair<std::string, float>> Tester::getResult() {
	return _Result;
}