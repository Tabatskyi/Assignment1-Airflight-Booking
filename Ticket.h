#pragma once
#include <string>
#include "Airplane.h"

using namespace std; 

class Ticket
{
public:
	Ticket(const shared_ptr<Seat>& InSeat, const shared_ptr<Airplane>& InFlight, const string& InPassenger, const string& InDate);
	~Ticket() = default;

	shared_ptr<Seat> GetSeat() const;
	shared_ptr<Airplane> GetFlight() const;
	string GetPassenger() const;
	string GetDate() const;
	unsigned long GetID() const;

private:
	shared_ptr<Seat> seat;
	shared_ptr<Airplane> flight;
	string passenger;
	string date;
};