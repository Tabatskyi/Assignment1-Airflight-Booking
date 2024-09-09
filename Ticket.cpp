#include "Ticket.h"

Ticket::Ticket(const shared_ptr<Seat>& InSeat, const shared_ptr<Airplane>& InFlight, const string& InPassenger, const string& InDate)
	: seat(InSeat), flight(InFlight), passenger(InPassenger), date(InDate) {}

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

unsigned long Ticket::GetID() const
{
	return hash<string>{}(passenger + date + flight->GetDate() + flight->GetNumber() + to_string(seat->GetRow()) + seat->GetColumn());
}