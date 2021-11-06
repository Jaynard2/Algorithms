#include "RushHourTester.h"

void RushHourTester::addVehicle(int x, int y, char orient, Vehichle type) {

}

bool RushHourTester::Test() {

}

std::string RushHourTester::popError() {
	if (_Error == "") {
		return "";
	}
	auto temp = _Error;
	_Error = "";
	return temp;
}

char RushHourTester::cordianteHash(int x, int y, char orient, Vehichle type) {

}

void RushHourTester::unHash(char pos) {

}

std::string RushHourTester::SearchBoard() {

}
void RushHourTester::buildBoard(std::string) {

}

void RushHourTester::resetBoard() {
	for (int i = 0; i < 7; i++) {
		memset(_Board[i], 0, 7);
	}
}