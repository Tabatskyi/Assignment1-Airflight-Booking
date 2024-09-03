#pragma once

#include "iostream"

class Seat
{
public:
	Seat(int InRow, char InColumn);
	~Seat();

	void Book();
	void Unbook();

	unsigned int GetRow() const;
	char GetColumn() const;
	bool IsBooked() const;
	unsigned int GetPrice() const;

	void SetPrice(unsigned int InPrice);

private:
	unsigned int row;
	char column;
	bool booked;
	unsigned int price;
};