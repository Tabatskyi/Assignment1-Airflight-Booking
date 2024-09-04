#include "Airplane.h"

Airplane::Airplane(const string& InDate, const int& InColumns) : date(InDate), columns(InColumns) 
{
	for (int i = 0; i < rows; i++)
	{
		vector<Seat> row;
		seats.push_back(row);
	}
	rows = 0;
}

Airplane::~Airplane() {}

void Airplane::SetSeats(const unsigned int& startRow, const unsigned int& finishRow, const unsigned int& price) 
{
	for (int i = startRow; i <= finishRow; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			Seat seat(i, j + 65, price);
			seats[i].push_back(seat);
		}
		rows++;
	}
}

bool Airplane::CheckSeat(const unsigned int& row, const char& column)
{
	if (seats[row][column - 65].IsBooked())
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Airplane::BookSeat(const unsigned int& row, const char& column)
{
	seats[row][column - 65].Book();
}