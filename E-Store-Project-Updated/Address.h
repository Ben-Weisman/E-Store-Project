#ifndef __Address_h
#define __Address_h

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
	 const char* getCountry()const;
	 const char* getCity()const;
	 const char* getStreet()const;
	 int getHouseNumber()const;
public:
	 void showAddress()const;

};
#endif // !__Address_h