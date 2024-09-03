#pragma once
class Seat
{
public:
	Seat(int InRow, char InColumn);
	~Seat();

	int GetRow() const;
	char GetColumn() const;

private:
	int row;
	char column;
};

