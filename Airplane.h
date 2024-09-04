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
	bool CheckSeat(const unsigned int& row, const char& column);
	void BookSeat(const unsigned int& row, const char& column);

private:
	int rows;
	int columns;
	const string date;
	vector<vector<Seat>> seats;
};