#pragma once
#include <string>
#include "Airplane.h"

using namespace std; 

class Ticket
{
public:
	Ticket(const Seat& InSeat, const Airplane& InFlight, const string& InPassenger, const string& InDate, const string& InTime);
	~Ticket();


private:
	Seat seat;
	Airplane flight;
	string passenger;
	string date;
	string time;
};