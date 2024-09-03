#include "Seat.h"

Seat::Seat(int InRow, char InColumn) : row(InRow), column(InColumn) 
{
	booked = false;
	price = 0;
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

void Seat::SetPrice(unsigned int InPrice)
{
	price = InPrice;
}

unsigned int Seat::GetPrice() const 
{
	return price;
}