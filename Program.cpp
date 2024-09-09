#include "Ticket.h"
#include "Parser.h"
#include "FileReader.h"
#include <map>


using namespace std;

map<tuple<string, string>, shared_ptr<Airplane>> flightPlaneMap = {}; // (Date, Flight Number): Airplane
map<unsigned long, shared_ptr<Ticket>> ticketIDMap = {}; // ID: Ticket
map<string, vector<shared_ptr<Ticket>>> ticketPassengerMap = {}; // Passenger: Tickets[]
map<tuple<string, string>, vector<shared_ptr<Ticket>>> flightTicketsMap = {}; // (Date, Flight Number): Tickets[]
unique_ptr<FileReader> fileReader = make_unique<FileReader>();
unique_ptr<Parser> parser = make_unique<Parser>();

void check(const string date, const string flightNumber)
{
	tuple<string, string> key = make_tuple(date, flightNumber);
	if (!flightPlaneMap.count(key))
	{
		cout << "Flight " << flightNumber << " on " << date << " does not exist" << endl;
		return;
	}
	shared_ptr<Airplane> airplane = flightPlaneMap[key];

	vector<shared_ptr<Seat>> availableSeats = airplane->CheckSeats();
	cout << "Available seats for flight " << flightNumber << " on " << date << " are: ";
	for (int i = 0; i < availableSeats.size() - 1; i++)
	{
		shared_ptr<Seat> current = availableSeats[i];
		cout << current->GetRow() << current->GetColumn() << " " << current->GetPrice() << "$, ";
	}
	cout << availableSeats[availableSeats.size() - 1]->GetRow() << availableSeats[availableSeats.size() - 1]->GetColumn() << " " << availableSeats[availableSeats.size() - 1]->GetPrice() << "$" << endl;
}

void book(const string date, const string flightNumber, const string passenger, const string seat)
{
	shared_ptr<Airplane> airplane = flightPlaneMap[make_tuple(date, flightNumber)];
	unsigned int row;
	char column;

	if (seat.size() == 3) 
	{
		row = stoi(seat.substr(0, 2));
		column = seat[2];
	}
	else if (seat.size() == 2)
	{
		row = stoi(seat.substr(0, 1));
		column = seat[1];
	}
	else
	{
		cout << "Invalid seat format";
		return;
	}

	shared_ptr<Seat> seatToBook = airplane->GetSeat(row, column);
	if (seatToBook == nullptr)
	{
		cout << "Seat " << seat << " is not available";
		return;
	}
	
	if (!airplane->BookSeat(seatToBook->GetRow(), seatToBook->GetColumn()))
	{
		cout << "Seat " << seat << " is already booked";
		return;
	}

	shared_ptr<Ticket> ticket = make_shared<Ticket>(seatToBook, airplane, passenger, date);
	ticketIDMap[ticket->GetID()] = ticket;
	vector<shared_ptr<Ticket>> passangersTickets = ticketPassengerMap[passenger];
	passangersTickets.push_back(ticket);
	ticketPassengerMap[passenger] = passangersTickets;
	vector<shared_ptr<Ticket>> flightTickets = flightTicketsMap[make_tuple(date, flightNumber)];
	flightTickets.push_back(ticket);
	flightTicketsMap[make_tuple(date, flightNumber)] = flightTickets;
	cout << "Ticket " << ticket->GetID() << " booked for " << passenger << " on flight " << flightNumber << " on " << date << " seat " << seat << endl;
}

void returnTicket(const unsigned long ticketID)
{
	if (!ticketIDMap.count(ticketID))
	{
		cout << "Ticket " << ticketID << " does not exist" << endl;
		return;
	}
	shared_ptr<Ticket> ticket = ticketIDMap[ticketID];
	ticket->GetSeat()->Unbook();
	ticketIDMap.erase(ticketID);
	vector<shared_ptr<Ticket>> passangersTickets = ticketPassengerMap[ticket->GetPassenger()];
	passangersTickets.erase(remove(passangersTickets.begin(), passangersTickets.end(), ticket), passangersTickets.end());
	cout << "Ticket " << ticketID << " returned" << endl;
}

void viewByID(const unsigned long ticketID) 
{
	if (!ticketIDMap.count(ticketID))
	{
		cout << "Ticket " << ticketID << " does not exist" << endl;
		return;
	}
	shared_ptr<Ticket> ticket = ticketIDMap[ticketID];
	cout << "Ticket " << ticketID << " for " << ticket->GetPassenger() << " on flight " << ticket->GetFlight()->GetDate() << " " << ticket->GetFlight()->GetNumber() << " seat " << ticket->GetSeat()->GetRow() << ticket->GetSeat()->GetColumn() << " " << ticket->GetSeat()->GetPrice() << "$" << endl;
}

void viewByPassenger(const string passenger)
{
	if (!ticketPassengerMap.count(passenger))
	{
		cout << "Passenger " << passenger << " does not have any tickets" << endl;
		return;
	}
	vector<shared_ptr<Ticket>> ticket = ticketPassengerMap[passenger];
	for (int i = 0; i < ticket.size(); i++)
	{
		cout << "Ticket " << ticket[i]->GetID() << " for " << passenger << " on flight " << ticket[i]->GetFlight()->GetDate() << " " << ticket[i]->GetFlight()->GetNumber() << " seat " << ticket[i]->GetSeat()->GetRow() << ticket[i]->GetSeat()->GetColumn() << " " << ticket[i]->GetSeat()->GetPrice() << "$" << endl;
	}
}

void viewFlight(const string date, const string number) 
{
	tuple<string, string> key = make_tuple(date, number);
	if (!flightPlaneMap.count(key))
	{
		cout << "Flight " << number << " on " << date << " does not exist" << endl;
		return;
	}
	vector<shared_ptr<Ticket>> tickets = flightTicketsMap[key];
	for (int i = 0; i < tickets.size(); i++)
	{
		cout << "Ticket " << tickets[i]->GetID() << " for " << tickets[i]->GetPassenger() << " on flight " << number << " on " << date << " seat " << tickets[i]->GetSeat()->GetRow() << tickets[i]->GetSeat()->GetColumn() << " " << tickets[i]->GetSeat()->GetPrice() << "$" << endl;
	}
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
		shared_ptr<Airplane> airplane = make_shared<Airplane>(parsedString[0], parsedString[1], stoi(parsedString[2]));
		for (int j = 3; j < parsedString.size(); j+=2)
		{
			vector<string> parcedRows = parser->Parse(parsedString[j], "-");
			string price = parsedString[j + 1];
			price.pop_back();
			airplane->SetSeats(stoi(parcedRows[0]), stoi(parcedRows[1]), stoi(price));
		}
		
        flightPlaneMap[make_tuple(parsedString[0], parsedString[1])] = airplane;
	}

	book("15.12.2022", "AB123", "Joe Mama", "9A");
	book("15.12.2022", "AB123", "Joe Mama", "1B");
	check("15.12.2022", "AB123");
	returnTicket(1760443121);
	check("15.12.2022", "AB123");
	viewByID(1758872336);
	book("18.12.2022", "CD456", "Joe Mama", "40G");
	viewByPassenger("Joe Mama");
	check("18.12.2022", "CD456");
	viewFlight("18.12.2022", "CD456");
	
	return 0;
}