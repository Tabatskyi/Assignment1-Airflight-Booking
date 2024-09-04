#include "Ticket.h"
#include "Parser.h"
#include "FileReader.h"
#include <map>

using namespace std;

int main() 
{
	map<string, Airplane> flightPlaneMap = {};
	unique_ptr<FileReader> fileReader = make_unique<FileReader>();
	unique_ptr<Parser> parser = make_unique<Parser>();
	string filename;

	cout << "Hello";
	cin >> filename;
	
	vector<string> fileContent = fileReader->ReadFile(filename);
	
	for (int i = 1; i < fileContent.size(); i++)
	{
		vector<string> parsedString = parser->Parse(fileContent[i], " ");
		Airplane airplane(parsedString[0], stoi(parsedString[2]));
		for (int j = 3; j < parsedString.size(); j+=2)
		{
			vector<string> parcedRows = parser->Parse(parsedString[j], "-");
			string price = parsedString[j + 1];
			price.pop_back();
			airplane.SetSeats(stoi(parcedRows[0]), stoi(parcedRows[1]), stoi(price));
		}
		
		flightPlaneMap.insert(pair<string, Airplane>(parsedString[1], airplane));
	}
	
	return 0;
}