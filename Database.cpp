#include "Database.h"

using namespace std;

void Database::AddAirplane(const string date, const string flightNumber, const shared_ptr<Airplane> airplane)
{
	airplanes.push_back(airplane);
}

void Database::AddTicket(const shared_ptr<Airplane> airplane, const string passenger, const shared_ptr<Seat> seat)
{
	string date = airplane->GetDate();
	string flightNumber = airplane->GetNumber();
	shared_ptr<Ticket> ticket = make_shared<Ticket>(seat, airplane, passenger, date);
	tickets.push_back(ticket);
}

shared_ptr<Airplane> Database::GetAirplane(const string date, const string flightNumber)
{
	for (shared_ptr<Airplane> airplane : airplanes)
	{
		if (airplane->GetDate() == date && airplane->GetNumber() == flightNumber)
			return airplane;
	}
	return nullptr;
}

shared_ptr<Ticket> Database::GetTicket(const unsigned long id)
{
	for (shared_ptr<Ticket> ticket : tickets)
	{
		if (ticket->GetID() == id)
			return ticket;
	}
	return nullptr;
}

vector<shared_ptr<Ticket>> Database::GetTickets(const string passenger)
{
	vector<shared_ptr<Ticket>> passengersTicket;
	for (shared_ptr<Ticket> ticket : tickets)
	{
		if (ticket->GetPassenger() == passenger)
			passengersTicket.push_back(ticket);
	}
	return passengersTicket;
}

vector<shared_ptr<Ticket>> Database::GetTickets(const string date, const string flightNumber)
{
	vector<shared_ptr<Ticket>> airplaneTicket;
	for (shared_ptr<Ticket> ticket : tickets)
	{
		if (ticket->GetFlight()->GetNumber() == flightNumber && ticket->GetDate() == date)
			airplaneTicket.push_back(ticket);
	}
	return airplaneTicket;
}

void Database::RemoveTicket(shared_ptr<Ticket> ticket) 
{
	unsigned long id = ticket->GetID();
	string passenger = ticket->GetPassenger();
	string date = ticket->GetDate();
	string flightNumber = ticket->GetFlight()->GetNumber();

	tickets.erase(remove(tickets.begin(), tickets.end(), ticket), tickets.end());
}