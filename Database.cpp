#include "Database.h"

using namespace std;

void Database::AddAirplane(const string date, const string flightNumber, const shared_ptr<Airplane> airplane)
{
	flightPlaneMap[make_tuple(date, flightNumber)] = airplane;
}

void Database::AddTicket(const shared_ptr<Airplane> airplane, const string passenger, const shared_ptr<Seat> seat)
{
	string date = airplane->GetDate();
	string flightNumber = airplane->GetNumber();
	shared_ptr<Ticket> ticket = make_shared<Ticket>(seat, airplane, passenger, date);
	idTicketMap[ticket->GetID()] = ticket;
	passengerTicketsMap[passenger].push_back(ticket);
	flightTicketsMap[make_tuple(date, flightNumber)].push_back(ticket);
}

shared_ptr<Airplane> Database::GetAirplane(const string date, const string flightNumber)
{
	return flightPlaneMap[make_tuple(date, flightNumber)];
}

shared_ptr<Ticket> Database::GetTicket(const unsigned long id)
{
	return idTicketMap[id];
}

vector<shared_ptr<Ticket>> Database::GetTickets(const string passenger)
{
	if (passengerTicketsMap.count(passenger))
		return passengerTicketsMap[passenger];
	return {};
}

vector<shared_ptr<Ticket>> Database::GetTickets(const string date, const string flightNumber)
{
	if (flightTicketsMap.count(make_tuple(date, flightNumber)))
		return flightTicketsMap[make_tuple(date, flightNumber)];
	return {};
}

void Database::RemoveTicket(shared_ptr<Ticket> ticket) 
{
	unsigned long id = ticket->GetID();
	string passenger = ticket->GetPassenger();
	string date = ticket->GetDate();
	string flightNumber = ticket->GetFlight()->GetNumber();

	idTicketMap.erase(id);
	vector<shared_ptr<Ticket>> passangersTickets = passengerTicketsMap[passenger];
	passangersTickets.erase(remove(passangersTickets.begin(), passangersTickets.end(), ticket), passangersTickets.end());
	passengerTicketsMap[passenger] = passangersTickets;
	vector<shared_ptr<Ticket>> flightTickets = flightTicketsMap[make_tuple(date, flightNumber)];
	flightTickets.erase(remove(flightTickets.begin(), flightTickets.end(), ticket), flightTickets.end());
	flightTicketsMap[make_tuple(date, flightNumber)] = flightTickets;
}