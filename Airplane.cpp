#include "Airplane.h"

Airplane::Airplane(const string& InDate, const string& InNumber, const int& InColumns) : date(InDate), number(InNumber), columns(InColumns)
{
	for (int i = 0; i < columns; i++)
	{
		vector<shared_ptr<Seat>> col;
		seats.push_back(col);
	}
	rows = 0;
}

void Airplane::SetSeats(const unsigned int& startRow, const unsigned int& finishRow, const unsigned int& price) 
{
	for (int i = startRow; i <= finishRow; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			shared_ptr<Seat> seat = make_shared<Seat>(i, j + 65, price);
			seats[j].push_back(seat);
		}
		rows++;
	}
}

vector<shared_ptr<Seat>> Airplane::CheckSeats()
{
	vector<shared_ptr<Seat>> availableSeats;
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			if (!seats[i][j]->IsBooked())
			{
				availableSeats.push_back(seats[i][j]);
			}
		}
	}
	return availableSeats;
}

string Airplane::GetDate() const
{
	return date;
}

bool Airplane::BookSeat(const unsigned int& row, const char& column)
{
	shared_ptr<Seat> seatToBook = seats[column - 65][row - 1];
    if (seatToBook->IsBooked())
    {
        return false;
    }
    seatToBook->Book();
    return true;
}

shared_ptr<Seat> Airplane::GetSeat(const unsigned int& row, const char& column) const
{
	if (row >= rows || column - 65 > columns || column - 65 < 0) 
	{
		return nullptr;
	}
    return seats[column - 65][row - 1];
}

string Airplane::GetNumber() const
{
	return number;
}