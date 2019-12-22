#include "Date.h"

// --------------------- C'tor ---------------------

Date::Date(int day, int month, int year)
{

	setDay(day);
	setMonth(month);
	setYear(year);
}
  
// -----------------------------setters----------------------------------

bool Date::setDay(int day)
{
	if (day < 1 || day>31) 
	{// Validity check

		return false;
	}
	m_day = day;
	return true;
}
bool  Date::setMonth(int month)
{
	if (month < 1 || month>12)
	{// Validity check

		return false;
	}
	m_month = month;
	return true;
}
bool Date::setYear(int year)
{
	if (year < 0)  
	{// Validity check

		return false;
	}
	m_year = year;
	return true;
}

