#include "CSVWriter.h"
#include <exception>

CSVWriter::CSVWriter(std::string_view fileName) : _file(fileName.data())
{
	if (!_file.is_open())
	{
		throw std::exception("Failed to open file");
	}
}

CSVWriter::~CSVWriter() {
	_file.close();
}

void CSVWriter::nextCell()
{
	_file << ",";
}

void CSVWriter::nextcolumn()
{
	_file << "\n";
}

void CSVWriter::writeCurrentCell(std::string_view data)
{
	_file << data;
}
