#include <iostream>
#include <string>
#include <windows.h>
#include <ShObjIdl.h>
#include <fstream>
#include "GalexyTester.h"

int RunTests(std::fstream& fin, GalaxyTester& COBOL);
std::vector<std::string> stringSplit(std::string& in, char delim = ' ');
std::vector<int> sArraytoiArray(std::vector<std::string> in);

int main() {
	std::fstream filestream;
	GalaxyTester GT;

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

		switch (RunTests(filestream, GT)) {
		default:
			std::cout << "Read Finished" << std::endl;
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
		COBOL.initTest(params[0], params[1], params[3]);
		for (int j = 0; j < params[3] && !fin.fail() || !fin.eof(); j++) {
			temp = "";
			std::getline(fin, temp);
			COBOL.AddEvent(sArraytoiArray(stringSplit(temp, ' ')));
		}
		COBOL.Test();
	}
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