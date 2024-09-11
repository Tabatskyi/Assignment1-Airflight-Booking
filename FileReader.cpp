#include "FileReader.h"

vector<string> FileReader::ReadFile(const string& filename) 
{
	ifstream file(filename);
	vector<string> fileContent;

	if (file.is_open())
	{
		string line;
		while (getline(file, line))
		{
			if (!line.empty())
				fileContent.push_back(line);
		}
		file.close();
	}
}