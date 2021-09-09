#pragma once
#include <string>
#include <fstream>

class CSVWriter
{
public:
	CSVWriter(std::string_view fileName);
	~CSVWriter();

	void nextCell();
	void nextcolumn();
	void writeCurrentCell(std::string_view data);

	void operator<<(std::string input) {
		_file << input << ",";
	};

private:
	std::ofstream _file;

};

