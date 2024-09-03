#pragma once

#include <iostream>
#include <string>

using namespace std;

class FileReader
{
	FileReader();
	~FileReader();

	string ReadFile(const string& filename);
};

