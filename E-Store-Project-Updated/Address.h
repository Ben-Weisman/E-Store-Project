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
	inline bool setHouseNumber(const int number);
public:
	inline const char* getCountry()const;
	inline const char* getCity()const;
	inline const char* getStreet()const;
	inline int getHouseNumber()const;
public:
	inline void printAddress()const;

};
#endif // !__Address_h