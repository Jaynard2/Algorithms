#pragma once
#include <string>
#include <fstream>

class CSVWriter
{
public:
	CSVWriter(std::string_view fileName);

	void nextCell();
	void nextcolumn();
	void writeCurrentCell(std::string_view data);

private:
	std::ofstream _file;

};

