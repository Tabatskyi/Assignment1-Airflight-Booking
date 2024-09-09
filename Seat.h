#pragma once

#include "iostream"

class Seat
{
public:
	Seat(const unsigned int InRow, const char InColumn, const unsigned int InPrice);
	~Seat() = default;

	void Book();
	void Unbook();

	unsigned int GetRow() const;
	char GetColumn() const;
	bool IsBooked() const;
	unsigned int GetPrice() const;

private:
	const unsigned int row;
	const char column;
	const unsigned int price;
	bool booked;
};