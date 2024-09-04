#include "Airplane.h"

Airplane::Airplane(const string& InDate, const int& InColumns) : date(InDate), columns(InColumns) 
{
	for (int i = 0; i < columns; i++)
	{
		vector<Seat> col;
		seats.push_back(col);
	}
	rows = 0;
}

Airplane::~Airplane() {}

void Airplane::SetSeats(const unsigned int& startRow, const unsigned int& finishRow, const unsigned int& price) 
{
	for (int i = startRow - 1; i < finishRow; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			Seat seat(i, j + 65, price);
			seats[j].push_back(seat);
		}
		rows++;
	}
}

vector<Seat> Airplane::CheckSeats(const unsigned int& row, const char& column)
{
	vector<Seat> availableSeats;
	for (int i = 0; i < rows; i++)
	{
		if (!seats[row][column - 65].IsBooked())
		{
			availableSeats.push_back(seats[row][column - 65]);
		}
	}
	return availableSeats;
}

void Airplane::BookSeat(const unsigned int& row, const char& column)
{
	seats[row][column - 65].Book();
}