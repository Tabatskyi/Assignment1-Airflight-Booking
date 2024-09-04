#include "Ticket.h"
#include "Parser.h"
#include "FileReader.h"
#include <map>

using namespace std;

int main() 
{
	map<string, Airplane> flightPlaneMap = {};
	unique_ptr<FileReader> fileReader = make_unique<FileReader>();
	unique_ptr<Parser> parser = make_unique<Parser>(" ");
	string filename;

	cout << "Hello";
	cin >> filename;
	
	vector<string> fileContent = fileReader->ReadFile(filename);
	
	for (int i = 0; i < fileContent.size(); i++)
	{
		vector<string> parsedString = parser->Parse(fileContent[0]);
		Airplane airplane(parsedString[0], stoi(parsedString[2]));
		for (int j = 2; j < parsedString.size(); j++)
		{
			vector<string> parcedRows = parser->Parse(parsedString[j]);
			string price = parcedRows[j + 1];
			price.pop_back();
			airplane.SetSeats(stoi(parcedRows[0]), stoi(parcedRows[1]), stoi(price));
		}
		
		flightPlaneMap.insert(pair<string, Airplane>(parsedString[0], airplane));
	}
	
	return 0;
}