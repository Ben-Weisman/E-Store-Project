#ifndef __User_h
#define __User_h
#include <iostream>
#include "Address.h"
using namespace std;

class User
{
protected:

	char* m_username;
	char* m_password;
	char* m_fname;
	char* m_lname;

	Address m_address;

public:
	~User(); // d'tor
	User(const char* userName,const char* password,const char* fname,const char*
		lname, const Address& address);
	User(const User& u); //copy c'tor
	
public:

	bool setUsername(const char* username);
	bool setPassword(const char* password);
	bool setFname(const char* fname);
	bool setLname(const char* lname);
	bool setAddress(const Address& address); // ####### Need to implement

	inline  const char* getFirstName()const { return m_fname; }
	inline  const char* getLastName()const { return m_lname; }
	inline  const char* getUsername()const { return m_username; }
	inline  const Address& getAddress()const { return m_address; }

public:
	void showUser(); // Not finished - polymorphism
	const User& operator=(const User& other);
	friend ostream& operator<<(ostream& os, const User& buyer);
};



#endif // !__User_h