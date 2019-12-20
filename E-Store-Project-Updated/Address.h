#ifndef __Address_h
#define __Address_h
#include <iostream>
using namespace std;

class Address
{
private:
	char* m_country;
	char* m_city;
	char* m_street;
	int m_house_number;

public:
	Address(char* country, char* city, char* street, int number); //c'tor
	~Address();// d'tor
	Address(const Address&a); //copy c'tor
	Address(Address&&a); //move c'tor
public:
	bool setCountry(const char* country);
	bool setCity(const char* city);
	bool setStreet(const char* street);
	 bool setHouseNumber(const int number);
public:
	inline const char* getCountry()const { return m_country; }
	inline const char* getCity()const { return m_city; }
	inline const char* getStreet()const{ return m_street;}
	inline int getHouseNumber()const { return m_house_number; }
public:
	inline void showAddress()const {cout << m_country << ", " << m_city << ", " << m_house_number << " " << m_street << " st" << endl;}

};
#endif // !__Address_h