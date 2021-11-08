#include "RushHourTester.h"


bool RushHourTester::Test() {
	std::string base = "";
	auto n = _SearchResults.emplace(SearchBoard(), base).first;
	_work.push(n);

	while(!_work.empty())
	{
		buildBoard(_work.front()->first);
		for (int i = 0; i < _work.front()->first.length(); i++) {
			Position current = unHash(_work.front()->first[i]);
			auto result = shift(current, _work.front()->first);
			if (result != "") { //Returns True if Red Car Escaps	
				_Final = result;
				return true;
			}
			
		}

		_work.pop();
	}
	_Error = "Solution Not Found";
	return false;
}

RushHourTester::RushHourTester()
{
	resetBoard();
	_Final = "";
}

RushHourTester::~RushHourTester()
{
}

void RushHourTester::addVehicle(int x, int y, char orient, Vehicle type) {
	if (orient == 'h') {
		int length = x + type;
		length -= 2 * (type == Red);
		for (int i = x; i < length; i++) {
			_Board[i][y] = type;
		}
	}
	else if (orient == 'v') {
		for (int j = y; j < (y + type); j++) {
			_Board[x][j] = type + 10;
		}
	}
}

std::string RushHourTester::popError() {
	if (_Error == "") {
		return "";
	}
	auto temp = _Error;
	_Error = "";
	return temp;
}

unsigned char RushHourTester::coordinateHash(int x, int y, char orient, Vehicle type) 
{
	bool isRed = type == Red;
	return (x << 5) + ((y | isRed * 7) << 2) + ((orient == 'v') << 1) + (type - 2) * !isRed;
}

Position RushHourTester::unHash(unsigned char pos) 
{
	int x = pos >> 5;
	int y = (pos & 0x1C) >> 2;
	Vehicle type;
	if (y == 7)
	{
		type = Red;
		y = 3;
	}
	else
	{
		type = (Vehicle)((pos & 0x01) + 2);
	}
	char orient = ((pos & 0x02) ? 'v' : 'h');
	

	return { x, y, orient, type };
}

std::string RushHourTester::SearchBoard() {
	std::string BoardHash = "";
	for (int i = 1; i < 7; i++) {
		for (int j = 1; j < 7; j++) {
			int val = _Board[i][j];
			if (val == 0) {
				continue;
			}
			else if (val > 10) {
				//vertial
				val -= 10;
				BoardHash += coordinateHash(i, j, 'v', (Vehicle)val);
				Position veh = {i, j, 'v', (Vehicle)val};
				RemoveVehicle(veh);
			}
			else {
				BoardHash += coordinateHash(i, j, 'h', (Vehicle)val);
				Position veh = {i, j, 'h', (Vehicle)val};
				RemoveVehicle(veh);
			}
		}
	}

	return BoardHash;
}
void RushHourTester::buildBoard(std::string input) {
	resetBoard();
	for (int i = 0; i < input.length(); i++) {
		auto temp = unHash(input[i]);
		addVehicle(temp.x, temp.y, temp.orient, temp.type);
	}
}

void RushHourTester::resetBoard() {
	_Board.fill(std::array<int, 7> { 0 });
}

std::string RushHourTester::shift(Position pos, std::string parent) {
	if (pos.orient == 'v') {
		//Vertical
		for (int i = pos.y - 1; i > 0; i--) {
			buildBoard(parent);
			if (_Board[pos.x][i] == 0) {
				RemoveVehicle(pos);
				addVehicle(pos.x, i, pos.orient, pos.type);
				std::string test = SearchBoard();
				if (_SearchResults.find(test) == _SearchResults.end()) {
					auto n = _SearchResults.insert(std::make_pair(test, parent)).first;
					_work.push(n);
				}
			}
			else {
				break;
			}
		}
		for (int i = pos.y + pos.type; i < 7; i++) {
			buildBoard(parent);
			if (_Board[pos.x][i] == 0) {
				RemoveVehicle(pos);
				addVehicle(pos.x, (i - pos.type + 1), pos.orient, pos.type);
				std::string test = SearchBoard();
				if (_SearchResults.find(test) == _SearchResults.end()) {
					auto n = _SearchResults.insert(std::make_pair(test, parent)).first;
					_work.push(n);
				}
			}
			else {
				break;
			}
		}
	}
	else {
		//horizontal
		for (int i = pos.x - 1; i > 0; i--) {
			buildBoard(parent);
			if (_Board[i][pos.y] == 0) {
				RemoveVehicle(pos);
				addVehicle(i, pos.y, pos.orient, pos.type);
				std::string test = SearchBoard();
				if (_SearchResults.find(test) == _SearchResults.end()) {
					auto n = _SearchResults.insert(std::make_pair(test, parent)).first;
					_work.push(n);
				}
			}
			else {
				break;
			}
		}
		bool isRed = pos.type == Red;
		int length = pos.type - 2 * isRed;
		for (int i = pos.x + length; i < 7; i++) {
			buildBoard(parent);
			if (_Board[i][pos.y] == 0) {
				RemoveVehicle(pos);
				addVehicle(i - length + 1, pos.y, pos.orient, pos.type);
				std::string test = SearchBoard();
				if (_SearchResults.find(test) == _SearchResults.end()) {
					auto n = _SearchResults.insert(std::make_pair(test, parent)).first;
					_work.push(n);
				}
				if (isRed && i == 6) {
					return test;
				}
			}
			else {
				break;
			}
		}
	}
	return "";
}

void RushHourTester::RemoveVehicle(Position pos) {
	if (pos.type == Red) {
		pos.type = Car;
	}
	if (pos.orient == 'h') {
		for (int i = pos.x; i < (pos.x + pos.type); i++) {
			_Board[i][pos.y] = 0;
		}
	}
	else {
		for (int i = pos.y; i < (pos.y + pos.type); i++) {
			_Board[pos.x][i] = 0;
		}
	}
}

std::vector<std::string> RushHourTester::Results() {
	std::vector<std::string> output;
	
	auto Node = _SearchResults.at(_Final);
	while (Node != "") {
		std::string board = "";
		buildBoard(Node);
		for (int i = 1; i < 7; i++) {
			for (int j = 1; j < 7; j++) {
				board += std::to_string(_Board[j][i]) + ", ";
			}
			board += "\n";
		}
		output.push_back(board);
		Node = _SearchResults.at(Node);
	}
	output.push_back("Iteration Count: " + std::to_string(output.size()));

	return output;
}