#include "Date.h"

// --------------------- C'tor ---------------------

Date::Date(int day, int month, int year)
{
	cout << endl << "########################################### IN DATE C'TOR ###########################################"<< endl;

	setDay(day);
	setMonth(month);
	setYear(year);
}
  
// -----------------------------setters----------------------------------

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
	if (year < 0)  
	{
		return false;
	}
	m_year = year;
	return true;
}

