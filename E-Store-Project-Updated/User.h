#ifndef __User_h
#define __User_h
#include <iostream>
#include "Address.h"
#include "Order.h"

using namespace std;

class User // Abstract class
{
protected:

	char* m_username;
	char* m_password;
	char* m_fname;
	char* m_lname;
	Address m_address;
	
protected:
	User(const char* userName, const char* password, const char* fname, const char*
		lname, const Address& address); // User is an abstract class - prevent from creating User obj.
	User(const User& u); //copy c'tor

protected:
	// Assume no changes are allowed after first initialization.
	bool setUsername(const char* username);
	bool setPassword(const char* password);
	bool setFname(const char* fname);
	bool setLname(const char* lname);
	bool setAddress(const Address& address);

public:
	virtual ~User(); // d'tor

	inline  const char* getFirstName()const { return m_fname; }
	inline  const char* getLastName()const { return m_lname; }
	inline  const char* getUsername()const { return m_username; }
	inline  const Address& getAddress()const { return m_address; }

public:
	const User& operator=(const User& other);
	friend ostream& operator<<(ostream& os, const User& buyer);
	virtual void toOs(ostream& os)const = 0 {}; // Make this class Abstract
};

#endif // !__User_h