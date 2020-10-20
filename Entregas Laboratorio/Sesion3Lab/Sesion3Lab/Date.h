#pragma once
#include <iostream>

using namespace std;

class Date
{
public:
	Date() : day(0), month(0), year(0) {};
	Date(int d, int m, int y);
	Date(const Date& date);
	void operator++();
	void operator+=(int n);
	bool operator<(const Date& date) const;
	int diff(const Date& date) const;
	void print() const;
	friend istream& operator>>(istream& in, Date& d);
	friend ostream& operator<<(ostream& in, const Date& d);
private:
	int day;
	int month;
	int year;

	int daysInMonth(int m) const;
	int calculateValue() const;
	bool correctDate() const;
};

