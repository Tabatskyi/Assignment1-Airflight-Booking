#pragma once

#include <vector>
#include <string>

using namespace std;

class Parser
{
public:
	Parser() {};
	~Parser() = default;
	vector<string> Parse(const string& InString, const string& InSeparator);
};

