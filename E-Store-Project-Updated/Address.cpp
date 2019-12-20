#include "Address.h"
#include "Utils.h"
#include <iostream>
using namespace std;

#pragma warning(disable:4996) 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Address::Address(char* country, char* city, char* street, int number) //c'tor
{
	cout << "\n########################################### IN ADDRESS C'TOR ###########################################\n";
	setCountry(country);
	setCity(city);
	setStreet(street);
	setHouseNumber(number);
}
Address::Address(const Address&a) //copy c'tor
{
	cout << "\n########################################### IN ADDRESS COPY ###########################################\n";
	setCountry(a.m_country);

	setCity(a.m_city);

	setStreet(a.m_street);

	setHouseNumber(a.m_house_number);

}
Address::Address(Address&&a) //move c'tor
{
	cout << "\n########################################### IN ADDRESS MOVE ###########################################\n";
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
	cout << "\n########################################### IN ADDRESS D'TOR ###########################################\n";
	delete[]m_country;
	delete[]m_city;
	delete[]m_street;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Address::setCountry(const char* country)
{
	int i = 0;
	while ((country[i] != '\0') && (isLetter(country[i]) || country[i] == ' '))
	{
		i++;
	}
	if (country[i] != '\0' || i <= 2)
	{
		return false;
	} //We assumed that There is no country with numbers/signs/less then 3 letters

	m_country = nullptr;
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

	m_city = nullptr;
	delete[] m_city;
	m_city = strdup(city);
	return true;
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

	m_street = nullptr;
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


void Address::showAddress()const
{
	cout << m_country << ", " << m_city << ", " << m_house_number << " " << m_street << "st." << endl;
}