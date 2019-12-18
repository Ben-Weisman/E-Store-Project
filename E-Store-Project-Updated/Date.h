#ifndef __Date_h
#define __Date_h

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
	 int getDay()const;
	 int getMonth()const;
	 int getYear()const;

public:
	 void showDate()const;
};

#endif //!__Date_h
