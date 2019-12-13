#include "Date.h"
#include <iostream>
using namespace std;

Date::Date(int day, int month, int year)
{
	setDay(day);
	setMonth(month);
	setYear(year);
}

bool Date::setDay(int day)
{
	if (day < 1 || day>31)
	{
		return false;
	}
	m_day = day;
	return true;
}
bool  Date::setMonth(int month)
{
	if (month < 1 || month>12)
	{
		return false;
	}
	m_month = month;
	return true;
}
bool Date::setYear(int year)
{
	if (year < 2019) //Before the year of the platfom creation ?
	{
		return false;
	}
	m_year=year;
	return true;
}


int Date::getDay()const
{
	return m_day;
}
int Date::getMonth()const
{
	return m_month;
}
int Date::getYear()const
{
	return m_year;

}

void Date::printDate()const
{
	cout << m_day << "/" << m_month << "/" << m_year << endl;
}