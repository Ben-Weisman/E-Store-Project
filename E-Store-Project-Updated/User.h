#ifndef __User_h
#define __User_h
#include <iostream>
#include "Address.h"
#include "Order.h"
#include <string>

using namespace std;

class User // Abstract class
{
protected:

	string m_username;
	string m_password;
	string m_fname;
	string m_lname;
	Address m_address;
	
protected:

	User(const string& userName, const string& password, const string& fname, const string&
		lname, const Address& address); // User is an abstract class - prevent from creating User obj.

	//@@@@ C'tor that gets ifStream @@@ 

	User(const User& u); //copy c'tor

	// Assume no changes are allowed after first initialization.
	bool setUsername(const string& username);
	bool setPassword(const string& password);
	bool setFname(const string& fname);
	bool setLname(const string& lname);
	bool setAddress(const Address& address);

public:

	inline  const string getFirstName()const { return m_fname; }
	inline  const string getLastName()const { return m_lname; }
	inline  const string getUsername()const { return m_username; }
	inline  const Address& getAddress()const { return m_address; }

public:
	const User& operator=(const User& other);
	friend ostream& operator<<(ostream& os, const User& buyer);
	virtual void toOs(ostream& os)const = 0 {}; // Make this class Abstract
	//@@ we need >> operator @@
};

#endif // !__User_h