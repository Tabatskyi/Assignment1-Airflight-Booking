#include "Ticket.h"
#include "Parser.h"
#include "FileReader.h"
#include <map>


using namespace std;

map<string, shared_ptr<Airplane>> flightPlaneMap = {}; // Flight Number: Airplane
map<unsigned long, shared_ptr<Ticket>> ticketIDMap = {}; // ID: Ticket
map<string, shared_ptr<Ticket>> ticketPassengerMap = {}; // Passenger: Ticket
unique_ptr<FileReader> fileReader = make_unique<FileReader>();
unique_ptr<Parser> parser = make_unique<Parser>();

static bool checkDate(const string date, const shared_ptr<Airplane> airplane) 
{
	if (airplane->GetDate() != date)
	{
		return false;
	}
	return true;

}

void check(const string date, const string flightNumber)
{
	shared_ptr<Airplane> airplane = flightPlaneMap.at(flightNumber);
	if (!checkDate(date, airplane)) 
	{
		cout << "Flight " << flightNumber << " is not available on " << date; 
		return; 
	}

	vector<shared_ptr<Seat>> availableSeats = airplane->CheckSeats();
	cout << "Available seats for flight " << flightNumber << " on " << date << " are: ";
	for (int i = 0; i < availableSeats.size(); i++)
	{
		cout << availableSeats[i]->GetRow() << availableSeats[i]->GetColumn() << " ";
	}
}

void book(const string date, const string flightNumber, const string passenger, const string seat)
{
	shared_ptr<Airplane> airplane = flightPlaneMap.at(flightNumber);
	if (!checkDate(date, airplane)) 
	{ 
		cout << "Flight " << flightNumber << " is not available on " << date;
		return; 
	}

	vector<shared_ptr<Seat>> availableSeats = airplane->CheckSeats();
	shared_ptr<Seat> seatToBook = airplane->GetSeat(stoi(seat.substr(0, 1)), seat[1]);
	
	bool success = airplane->BookSeat(seatToBook->GetRow(), seatToBook->GetColumn());
	if (!success)
	{
		cout << "Seat " << seat << " is already booked";
		return;
	}
	Ticket ticket(seatToBook, airplane, passenger, date, "00:00");
	unsigned long ticketID = hash<string>{}(passenger + date + flightNumber + seat);
	ticketIDMap.insert(make_pair(ticketID, make_shared<Ticket>(ticket)));
	cout << "Ticket booked for " << passenger << " on flight " << flightNumber << " on " << date << " at " << "00:00";
}

int main()  
{
	string configName;

	cout << "Hello";
	cin >> configName;
	
	vector<string> fileContent = fileReader->ReadFile(configName);
	
	for (int i = 1; i < fileContent.size(); i++)
	{
		vector<string> parsedString = parser->Parse(fileContent[i], " ");
		shared_ptr<Airplane> airplane = make_shared<Airplane>(parsedString[0], stoi(parsedString[2]));
		for (int j = 3; j < parsedString.size(); j+=2)
		{
			vector<string> parcedRows = parser->Parse(parsedString[j], "-");
			string price = parsedString[j + 1];
			price.pop_back();
			airplane->SetSeats(stoi(parcedRows[0]), stoi(parcedRows[1]), stoi(price));
		}
		
        flightPlaneMap.insert(make_pair(parsedString[1], move(airplane)));
	}

	book("15.12.2022", "AB123", "Joe Mama", "1A");
	book("15.12.2022", "AB123", "Joe Mama", "1B");
	check("15.12.2022", "AB123");
	
	return 0;
}