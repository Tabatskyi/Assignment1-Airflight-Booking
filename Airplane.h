#pragma once
#include <string>
#include <vector>
#include "Seat.h"

using namespace std;

class Airplane
{
public:
	Airplane(const int& InRows, const int& InColumns);
	~Airplane();

	void SetPrice(const unsigned int& startRow, const unsigned int& finishRow, const unsigned int& price);

private:
	int rows;
	int columns;
	vector<vector<Seat>> seats;
};