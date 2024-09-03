#pragma once

#include <vector>
#include <string>

using namespace std;

class Parser
{
public:
	Parser(const char& InSeparator);
	~Parser();
	vector<string> Parse(const string& str);
private:
	const char separator;
};

