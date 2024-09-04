#include "FileReader.h"

FileReader::FileReader() 
{

}

FileReader::~FileReader()
{

}

vector<string> FileReader::ReadFile(const string& filename) 
{
	vector<string> fileContent;
	string line;
	fileContent.push_back("Shliapa");
	fileContent.push_back("11.12.2022 FQ12 6 1-20 100$ 21-40 50$");
	return fileContent;
}