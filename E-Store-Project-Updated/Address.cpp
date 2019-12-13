#include "Address.h"
#include "utils.h"
#include <iostream>
using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Address::Address(char* country, char* city, char* street, int number) //c'tor
{
	setCountry(country);

	setCity(city);

	setStreet(street);

	setHouseNumber(number);

}
Address::Address(const Address&a) //copy c'tor
{
	setCountry(a.m_country);

	setCity(a.m_city);

	setStreet(a.m_street);

	setHouseNumber(a.m_house_number);

}
Address::Address(Address&&a) //move c'tor
{
	m_country = a.m_country;
	m_city = a.m_city;
	m_street = a.m_street;
	m_house_number = a.m_house_number;

	a.m_country = nullptr;
	a.m_city = nullptr;
	a.m_street = nullptr;
}
Address::~Address()// d'tor
{
	delete[]m_country;
	delete[]m_city;
	delete[]m_street;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Address::setCountry(const char* country)
{
	//need to check empy string
	int i = 0;
	while ((country[i] != '\0') && (isLetter(country[i]) || country[i] == ' '))
	{
		i++;
	}
	if (country[i] != '\0' || i <= 2)
	{
		return false;
	} //We assumed that There is no country with numbers/signs/less then 3 letters

	delete[] m_country;
	m_country = strdup(country);
	return true;
}
bool Address::setCity(const char* city)
{
	int i = 0;
	while ((city[i] != '\0') && (isLetter(city[i]) || city[i] == ' '))
	{
		i++;
	}
	if (city[i] != '\0' || i <= 1)
	{
		return false;
	} //We assumed that There is no city with numbers/signs/less then 2 letters 

	delete[] m_city;
	m_city = strdup(city);
	return true;
    exit();

}
bool Address::setStreet(const char* street)
{
	int i = 0;

	while (street[i] != '\0' && (isNumber(street[i]) || isLetter(street[i]) || street[i] == ' '))
	{
		i++;
	}
	if (street[i] != '\0' || i <= 1)
	{
		return false;
	} //We assumed that There street can be a word with numbers/letters and with more the 1 letter 

	delete[] m_street;
	m_street = strdup(street);
	return true;
}
bool Address::setHouseNumber(const int number)
{
	if (number <= 0)
		return false;

	m_house_number = number;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char* Address::getCountry()const
{
	return m_country;
}
const char* Address::getCity()const
{
	return m_city;
}
const char* Address::getStreet()const
{
	return m_street;
}
int Address::getHouseNumber()const
{
	return m_house_number;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Address::printAddress()const
{
	cout << m_country << ", " << m_city << ", " << m_house_number << " " << m_street << "st." << endl;
}