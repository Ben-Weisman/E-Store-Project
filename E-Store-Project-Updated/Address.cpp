#include "Address.h"
#include "Utils.h"

// --------------------- C'tor, Copy C'tor, D'tor, Move C'tor ---------------------

Address::Address(const string& country, const string& city, const string& street, int number) //c'tor
{
	setCountry(country);
	setCity(city);
	setStreet(street);
	setHouseNumber(number);
}
Address::Address(const Address&a) //copy c'tor
{
	*this = a; //using = operator
}
Address::Address(Address&&a) //move c'tor
{
	m_country=move(a.m_country);
	m_city = move(a.m_city);
	m_street = move(a.m_street);
	m_house_number = a.m_house_number;

	a.m_country = nullptr;
	a.m_city = nullptr;
	a.m_street = nullptr;
}
Address::~Address()// d'tor
{

}

// -----------------------------operators----------------------------------

const Address& Address::operator=(const Address& a)
{
	if (this != &a)
	{
		setCountry(a.m_country);

		setCity(a.m_city);

		setStreet(a.m_street);

		setHouseNumber(a.m_house_number);
	}
	return *this;
}

ostream& operator<<(ostream& os, const Address& address)
{
	os << address.m_country << ", " << address.m_city << ", " << address.m_house_number << " " << address.m_street << " st" << endl;

	return os;
}

// -----------------------------setters----------------------------------

bool Address::setCountry(const string& country)
{
	if (country.length() < 3)
		return false;//We assumed that There is no country with less then 3 letters

	m_country = country;
	return true;
}
bool Address::setCity(const string& city)
{	
	if (city.length()<3)// Validity check
		return false; //We assumed that There is no city with less then 3 letters 

	m_city = city;
	return true;
}
bool Address::setStreet(const string& street)
{

	if (street.length() < 3)// Validity check
		return false; //We assumed that the street should be word with more then 2 letters

	m_street = street;
	return true;
}
bool Address::setHouseNumber(const int number)
{
	if (number <= 0)// Validity check
		return false;

	m_house_number = number;
	return true;
}

