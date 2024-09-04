#include "Parser.h"

Parser::Parser(const string& InSeparator) : separator(InSeparator) {}
Parser::~Parser() {}

vector<string> Parser::Parse(const string& InString) 
{
	string str = InString;
    vector<std::string> tokens;
    size_t pos = 0;
    string token;
    while ((pos = str.find(separator)) != string::npos) 
    {
        token = str.substr(0, pos);
        tokens.push_back(token);
        str.erase(0, pos + separator.length());
    }
    tokens.push_back(str);

    return tokens;
}