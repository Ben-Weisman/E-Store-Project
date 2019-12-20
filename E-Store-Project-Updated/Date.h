#ifndef __Date_h
#define __Date_h
#include <iostream>
using namespace std;

class Date
{
	int m_day;
	int m_month;
	int m_year;


public:
	Date(int day, int month, int year);
	~Date() = default;

public:
	 bool setDay(int day);
	 bool setMonth(int month);
	 bool setYear(int year);

public:
	inline int getDay()const { return m_day; }
	inline int getMonth()const { return m_month; }
	inline int getYear()const { return m_year; }

public:
	inline void showDate()const { cout << m_day << "/" << m_month << "/" << m_year << endl; }
};

#endif //!__Date_h
