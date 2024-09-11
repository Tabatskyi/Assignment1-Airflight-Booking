#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class FileReader
{
public:
	vector<string> ReadFile(const string& filename);

private:
	ifstream file;
};