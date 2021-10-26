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