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
	inline bool setDay(int day);
	inline bool setMonth(int month);
	inline bool setYear(int year);

public:
	inline int getDay()const;
	inline int getMonth()const;
	inline int getYear()const;

public:
	inline void showDate()const;
};

#endif //!__Date_h
