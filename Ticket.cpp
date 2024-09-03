#include "Ticket.h"

Ticket::Ticket(const Seat& InSeat, const Airplane& InFlight, const string& InPassenger, const string& InDate, const string& InTime)
	: seat(InSeat), flight(InFlight), passenger(InPassenger), date(InDate), time(InTime) {}

Ticket::~Ticket() 
{

}