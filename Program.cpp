#include "Parser.h"
#include "Database.h"
#include "FileReader.h"
#include <algorithm>
#include <iostream>


using namespace std;

unique_ptr<FileReader> fileReader = make_unique<FileReader>();
unique_ptr<Parser> parser = make_unique<Parser>();
unique_ptr<Database> database = make_unique<Database>();

void check(const string date, const string flightNumber)
{
	shared_ptr<Airplane> airplane = database->GetAirplane(date, flightNumber);
	if (airplane == nullptr)
	{
		cout << "Flight " << flightNumber << " on " << date << " does not exist" << endl;
		return;
	}

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
	shared_ptr<Airplane> airplane = database->GetAirplane(date, flightNumber);
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
		cout << "Invalid seat format" << endl;
		return;
	}

	shared_ptr<Seat> seatToBook = airplane->GetSeat(row, column);
	if (seatToBook == nullptr)
	{
		cout << "Seat " << seat << " is not available" << endl;
		return;
	}
	
	if (!airplane->BookSeat(seatToBook->GetRow(), seatToBook->GetColumn()))
	{
		cout << "Seat " << seat << " is already booked" << endl;
		return;
	}

	shared_ptr<Ticket> ticket = make_shared<Ticket>(seatToBook, airplane, passenger, date);
	database->AddTicket(airplane, passenger, seatToBook);
	cout << "Ticket " << ticket->GetID() << " booked for " << passenger << " on flight " << flightNumber << " on " << date << " seat " << seat << endl;
}

void returnTicket(const unsigned long ticketID)
{
	shared_ptr<Ticket> ticket = database->GetTicket(ticketID);
	if (ticket == nullptr)
	{
		cout << "Ticket " << ticketID << " does not exist" << endl;
		return;
	}
	ticket->GetSeat()->Unbook();
	database->RemoveTicket(ticket);

	cout << "Ticket " << ticketID << " returned" << endl;
}
//view ID
void view(const unsigned long ticketID) 
{
	shared_ptr<Ticket> ticket = database->GetTicket(ticketID);
	if (ticket == nullptr)
	{
		cout << "Ticket " << ticketID << " does not exist" << endl;
		return;
	}
	cout << "Ticket " << ticketID << " for " << ticket->GetPassenger() << " on flight " << ticket->GetFlight()->GetDate() << " " << ticket->GetFlight()->GetNumber() << " seat " << ticket->GetSeat()->GetRow() << ticket->GetSeat()->GetColumn() << " " << ticket->GetSeat()->GetPrice() << "$" << endl;
}
//view Username
void view(const string passenger)
{
	vector<shared_ptr<Ticket>> tickets = database->GetTickets(passenger);
	if (tickets.size() < 1)
	{
		cout << "Passenger " << passenger << " does not have any tickets" << endl;
		return;
	}
	for (int i = 0; i < tickets.size(); i++)
	{
		cout << "Ticket " << tickets[i]->GetID() << " for " << passenger << " on flight " << tickets[i]->GetFlight()->GetDate() << " " << tickets[i]->GetFlight()->GetNumber() << " seat " << tickets[i]->GetSeat()->GetRow() << tickets[i]->GetSeat()->GetColumn() << " " << tickets[i]->GetSeat()->GetPrice() << "$" << endl;
	}
}
//view date flightNo
void view(const string date, const string number) 
{
	vector<shared_ptr<Ticket>> tickets = database->GetTickets(date, number);
	if (tickets.size() < 1)
	{
		cout << "Flight " << number << " on " << date << " does not have any booked tickets" << endl;
		return;
	}
	for (int i = 0; i < tickets.size(); i++)
	{
		cout << "Ticket " << tickets[i]->GetID() << " for " << tickets[i]->GetPassenger() << " on flight " << number << " on " << date << " seat " << tickets[i]->GetSeat()->GetRow() << tickets[i]->GetSeat()->GetColumn() << " " << tickets[i]->GetSeat()->GetPrice() << "$" << endl;
	}
}

int main()  
{
	string configName = "config";
	vector<string> fileContent = fileReader->ReadFile(configName);
	if (fileContent.size() < 2) 
	{
		cout << "Invalid config file";
		return 1;
	}
	
	for (int i = 1; i < fileContent.size(); i++)
	{
		vector<string> parsedString = parser->Parse(fileContent[i], " ");
		string date = parsedString[0];
		string number = parsedString[1];
		unsigned int columns = stoi(parsedString[2]);
		shared_ptr<Airplane> airplane = make_shared<Airplane>(date, number, columns);
		for (int j = 3; j < parsedString.size(); j+=2)
		{
			string rows = parsedString[j];
			vector<string> parcedRows = parser->Parse(rows, "-");
			string price = parsedString[j + 1];
			price.pop_back();
			unsigned int startRow = stoi(parcedRows[0]);
			unsigned int finishRow = stoi(parcedRows[1]);
			airplane->SetSeats(startRow, finishRow, stoi(price));
		}
		
		database->AddAirplane(date, number, airplane);
	}

	string input;
	do 
	{
		cout << ">";
		vector<string> parsedInput;
		getline(cin, input);

		if (input.empty())
			continue;

		parsedInput = parser->Parse(input, " ");

		string command = parsedInput[0];
		if (command == "check")
		{
			if (parsedInput.size() < 3)
			{
				cout << "Invalid input" << endl;
				continue;
			}
			string date = parsedInput[1];
			string flightNumber = parsedInput[2];
			check(date, flightNumber);
		}
		else if (command == "book")
		{
			if (parsedInput.size() < 5)
			{
				cout << "Invalid input" << endl;
				continue;
			}
			string date = parsedInput[1];
			string number = parsedInput[2];
			string passenger = parsedInput[3];
			if (parsedInput.size() > 5)
				for (int i = 4; i < parsedInput.size() - 1; i++)
					passenger += " " + parsedInput[i];
			string seat = parsedInput.back();
			book(date, number, passenger, seat);
		}
		else if (command == "return")
		{
			if (parsedInput.size() < 2)
			{
				cout << "Invalid input" << endl;
				continue;
			}
			unsigned long ticketID = stoul(parsedInput[1]);
			returnTicket(ticketID);
		}
		else if (command == "view")
		{
			if (parsedInput.size() < 2)
			{
				cout << "Invalid input" << endl;
				continue;
			}
			string type = parsedInput[1];
			if (!any_of(type.begin(), type.end(), isdigit))
			{
				if (parsedInput.size() > 2)
					for (int i = 2; i < parsedInput.size(); i++)
						type += " " + parsedInput[i];

				view(type); 
			}
			else
			{
				if (all_of(type.begin(), type.end(), isdigit))
				{
					unsigned long ticketID = stoul(type);
					view(ticketID);
				}
				else if (parser->Parse(type, ".").size() == 3)
				{
					string date = type;
					string number = parsedInput[2];
					view(date, number);
				}
			}
		}
		else if (command == "help")
			cout << "Commands:\n check date flightNo\n book date flightNo place Username\n return ID\n view ID\n view Username\n view date flightNo\n help\n quit" << endl;
		else if (command == "quit")
			cout << "Goodbye!" << endl;
		else
			cout << "Invalid command" << endl;
	} 
	while (input != "quit");
	
	return 0;
}