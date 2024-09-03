#pragma once
#include <string>
#include "Seat.h"

using namespace std; 

class Ticket
{
public:
	Ticket(const Seat& InSeat, const string& flight, const string& passenger, const string& date, const string& time);
	~Ticket();


private:
	Seat seat;
	string flight;
	string passenger;
	string date;
	string time;
};

