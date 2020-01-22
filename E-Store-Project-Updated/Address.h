#ifndef __Address_h
#define __Address_h
#include <iostream>
#include <string>
using namespace std;

class Address
{
private:
	string m_country;
	string m_city;
	string m_street;
	int m_house_number;

public:
	Address(const string& country, const string& city, const string& street, int number); //c'tor
	~Address();// d'tor
	Address(const Address&a); //copy c'tor
	Address(Address&&a); //move c'tor
public:
	const Address& operator=(const Address& a);
	friend ostream& operator<<(ostream& os, const Address& address);

public:
	bool setCountry(const string& country);
	bool setCity(const string& city);
	bool setStreet(const string& street);
	 bool setHouseNumber(const int number);
public:
	inline const string& getCountry()const { return m_country; }
	inline const string& getCity()const { return m_city; }
	inline const string& getStreet()const{ return m_street;}
	inline int getHouseNumber()const { return m_house_number; }

};
#endif // !__Address_h