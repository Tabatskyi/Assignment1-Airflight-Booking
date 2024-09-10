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
	map<tuple<string, string>, shared_ptr<Airplane>> flightPlaneMap; // (Date, Flight Number): Airplane
	map<unsigned long, shared_ptr<Ticket>> idTicketMap; // ID: Ticket
	map<string, vector<shared_ptr<Ticket>>> passengerTicketsMap; // Passenger: Tickets[]
	map<tuple<string, string>, vector<shared_ptr<Ticket>>> flightTicketsMap; // (Date, Flight Number): Tickets[]
};

