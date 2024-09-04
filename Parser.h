#pragma once

#include <vector>
#include <string>

using namespace std;

class Parser
{
public:
	Parser(const string& InSeparator);
	~Parser();
	vector<string> Parse(const string& InString);
private:
	const string separator;
};

