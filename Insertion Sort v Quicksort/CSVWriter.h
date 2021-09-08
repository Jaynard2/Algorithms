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

	std::fstream operator<<(std::string input) {
		std::fstream output;
		output << input;
		return output;
	};

private:
	std::ofstream _file;

};

