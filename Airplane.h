#pragma once
#include <string>
#include <vector>
#include "Seat.h"

using namespace std;

class Airplane
{
public:
	Airplane(const string& InDate, const int& InColumns);
	~Airplane();

	void SetSeats(const unsigned int& startRow, const unsigned int& finishRow, const unsigned int& price);
	vector<shared_ptr<Seat>> CheckSeats();
	bool BookSeat(const unsigned int& row, const char& column);
	string GetDate() const;
	shared_ptr<Seat> GetSeat(const unsigned int& row, const char& column) const;

private:
	int rows;
	int columns;
	const string date;
	vector<vector<shared_ptr<Seat>>> seats; // colummns[rows]
};