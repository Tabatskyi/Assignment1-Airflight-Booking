#pragma once

#include <vector>
#include <string>

using namespace std;

class Parser
{
public:
	Parser();
	~Parser();
	vector<string> Parse(const string& InString, const string& InSeparator);
};

