#include "FileReader.h"

FileReader::FileReader() {}
FileReader::~FileReader(){}

vector<string> FileReader::ReadFile(const string& filename) 
{
	ifstream file(filename);
	vector<string> fileContent;
	string line;
	while (getline(file, line))
	{
		fileContent.push_back(line);
	}
	file.close();
	return fileContent;
}