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

int main() {
	std::fstream filestream;
	GalaxyTester GT;

	//set for calling the open file dialge from the windows api
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	IFileOpenDialog* pFileOpen;
	// Create the FileOpenDialog object.
	hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));
	hr = pFileOpen->Show(NULL);


	if(SUCCEEDED(hr)) {
		IShellItem* pItem;
		hr = pFileOpen->GetResult(&pItem);
		PWSTR filename;
		hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &filename);
		//attempt to open the given file
		try {
			filestream.open(filename, std::ios_base::in);
		}
		catch (std::ios_base::failure e) {
			std::cout << "File Failed to Open" << std::endl;
			return -1;
		}
		pItem->Release();
		pFileOpen->Release();
		CoUninitialize();
		std::cout << "SUCCESS opened file: " << filename << std::endl;

		//Parse the file and run the test. Each test is run once enough of the file is parsed
		switch (RunTests(filestream, GT)) {
		case(-1) :
			std::cout << "Invalid Problem count" << std::endl;
			break;
		case(-2) :
			std::cout << "Invalid Galaxy Dementions" << std::endl;
			break;
		default:
			std::cout << "Read Finished" << std::endl;
		}

		//print out the result
		for (auto obj : GT.getResult()) {
			std::cout << obj << std::endl;
		}
	}
	else {
		std::cout << "Failed to open file" << std::endl;
	}
	return 0;
}

int RunTests(std::fstream& fin, GalaxyTester& COBOL) {
	uint32_t testnumber = 0;
	std::string temp = "";

	//parse the number of tests to run
	if (!fin.fail() || !fin.eof()) {
		std::getline(fin, temp);
		testnumber = std::stoi(temp);
		if (testnumber < 0) {
			//return error if it is not a number
			return -1;
		}
	}
	//parse each test
	for (int i = 0; i < testnumber && !fin.fail() && !fin.eof(); i++) {
		temp = "";
		std::getline(fin, temp);
		//parse out the parameters for size of Galexy 0:3 and number of kingdoms 4
		auto params = sArraytoiArray(stringSplit(temp, ' '));
		if (params.size() < 4) {
			return -2;
		}
		COBOL.initTest(params[0], params[1], params[2]);
		//parse out each kindom
		for (int j = 0; j < params[3] && !fin.fail() && !fin.eof(); j++) {
			temp = "";
			std::getline(fin, temp);
			COBOL.AddEvent(sArraytoiArray(stringSplit(temp, ' ')));
		}
		//exicute test then continue to parse the rest of the tests
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