#include "Ticket.h"

Ticket::Ticket(const Seat& InSeat, const Airplane& InFlight, const string& InPassenger, const string& InDate, const string& InTime)
	: seat(InSeat), flight(InFlight), passenger(InPassenger), date(InDate), time(InTime) {}

Ticket::~Ticket() {}

Seat Ticket::GetSeat() const
{
	return seat;
}

Airplane Ticket::GetFlight() const
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