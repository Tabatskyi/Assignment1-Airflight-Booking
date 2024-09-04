#include "Seat.h"

Seat::Seat(const unsigned int InRow, const char InColumn, const unsigned int InPrice) : row(InRow), column(InColumn), price(InPrice)
{
	booked = false;
}
Seat::~Seat() {}

void Seat::Book() 
{
	booked = true;
}

void Seat::Unbook()
{
	booked = false;
}

bool Seat::IsBooked() const
{
	return booked;
}

unsigned int Seat::GetRow() const
{
	return row;
}

char Seat::GetColumn() const
{
	return column;
}

unsigned int Seat::GetPrice() const 
{
	return price;
}