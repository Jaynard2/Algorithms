#include "Tester.h"
#include <tuple>

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
			temp = new Intersection(INT_MAX, i, INT_MAX);
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
			_Result.push_back(obj.second + " " + std::to_string(_Parents.at(obj.first)->distance - distance));
		}
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

std::vector<std::string> Tester::getResult() {
	return _Result;
}