#include "Ticket.h"

Ticket::Ticket(const shared_ptr<Seat>& InSeat, const shared_ptr<Airplane>& InFlight, const string& InPassenger, const string& InDate, const string& InTime)
	: seat(InSeat), flight(InFlight), passenger(InPassenger), date(InDate), time(InTime) {}

Ticket::~Ticket() {}

shared_ptr<Seat> Ticket::GetSeat() const
{
	return seat;
}

shared_ptr<Airplane> Ticket::GetFlight() const
{
	return flight;
}

string Ticket::GetPassenger() const
{
	return passenger;
}

string Ticket::GetDate() const
{
	return date;
}

string Ticket::GetTime() const
{
	return time;
}