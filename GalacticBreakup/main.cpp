#include <iostream>
#include <string>
#include <windows.h>
#include <ShObjIdl.h>
#include <fstream>
#include "GalexyTester.h"

/*********************************************************
* Summary: The bottom up implementation for counting coins.
*
* Author: Nathanael Cook
* Created: Oct 2021
*
* Main class for reading in a test file and parasing it. Once input is parsed then
* it is passed to the tester.
*
* ©Copyright Cedarville University, its Computer Science faculty, and the
* authors. All rights reserved.
********************************************************/

int RunTests(std::fstream& fin, GalaxyTester& COBOL);
std::vector<std::string> stringSplit(std::string& in, char delim = ' ');
std::vector<int> sArraytoiArray(std::vector<std::string> in);

int main()
{
	GalaxyTester COBOL;

	std::string temp = "";

	temp = "";
	std::getline(std::cin, temp);
	auto params = sArraytoiArray(stringSplit(temp, ' '));
	if (params.size() < 4)
	{
		return -2;
	}
	COBOL.initTest(params[0], params[1], params[2]);
	for (int j = 0; j < params[3]; j++)
	{
		temp = "";
		std::getline(std::cin, temp);
		COBOL.AddEvent(sArraytoiArray(stringSplit(temp, ' ')));
	}
	COBOL.Test();

	for (auto obj : COBOL.getResult())
	{
		std::cout << obj << std::endl;
	}


	return 0;
}

int RunTests(std::fstream& fin, GalaxyTester& COBOL) {
	uint32_t testnumber = 0;
	std::string temp = "";
	if (!fin.fail() || !fin.eof()) {
		std::getline(fin, temp);
		testnumber = std::stoi(temp);
		if (testnumber < 0) {
			return -1;
		}
	}
	for (int i = 0; i < testnumber && !fin.fail() && !fin.eof(); i++) {
		temp = "";
		std::getline(fin, temp);
		auto params = sArraytoiArray(stringSplit(temp, ' '));
		if (params.size() < 4) {
			return -2;
		}
		COBOL.initTest(params[0], params[1], params[2]);
		for (int j = 0; j < params[3] && !fin.fail() && !fin.eof(); j++) {
			temp = "";
			std::getline(fin, temp);
			COBOL.AddEvent(sArraytoiArray(stringSplit(temp, ' ')));
		}
		COBOL.Test();
	}
	fin.close();
}

std::vector<std::string> stringSplit(std::string& in, char delim) 
{
	size_t begin = 0;
	size_t end = in.find(delim);

	std::vector<std::string> vec;
	do
	{
		vec.emplace_back(in, begin, end - begin);

		begin = end + 1;
		end = in.find(delim, begin);

	} while (begin != 0);

	return vec;
}

std::vector<int> sArraytoiArray(std::vector<std::string> in) 
{
	std::vector<int> vec;
	for (const auto& i : in)
	{
		vec.emplace_back(std::stoi(i));
	}

	return vec;
}