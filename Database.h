#pragma once
#include <iostream>
#include <algorithm>
#include <map>
#include "Ticket.h"

class Database
{
public:
	Database() {};
	~Database() = default;

	void AddAirplane(const string date, const string flightNumber, const shared_ptr<Airplane> airplane);
	void AddTicket(const shared_ptr<Airplane> airplane, const string passenger, const shared_ptr<Seat> seat);
	void RemoveTicket(shared_ptr<Ticket> ticket);

	shared_ptr<Airplane> GetAirplane(const string date, const string flightNumber);
	shared_ptr<Ticket> GetTicket(const unsigned long id);
	vector<shared_ptr<Ticket>> GetTickets(const string passenger);
	vector<shared_ptr<Ticket>> GetTickets(const string date, const string flightNumber);
private:
	vector<shared_ptr<Ticket>> tickets;
	vector<shared_ptr<Airplane>> airplanes;
};

