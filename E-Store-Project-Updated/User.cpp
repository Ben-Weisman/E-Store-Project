#include "User.h"
#include "Utils.h"
#pragma warning(disable:4996) 

/////////////////////////////////////////////////////////////////////////
// -------------------- C'tor, copy c'tor, d'tor -------------------- //
///////////////////////////////////////////////////////////////////////
User::User(const char* username,const char* password,const char* fname,const char* lname,
	const Address& address) : m_address(address) // c'tor
{
	setUsername(username);
	setPassword(password);
	setFname(fname);
	setLname(lname);
}


User::~User() // d'tor
{
	delete[]m_fname;
	delete[]m_lname;
	delete[]m_username;
	delete[]m_password;
}

User::User(const User& u) :m_address(u.m_address) // copy c'tor
{ // Don't use assignment operator due to the double assignment of address. Send to Address' copy instead
	setUsername(u.m_username);
	setPassword(u.m_password);
	setFname(u.m_fname);
	setLname(u.m_lname);
}

const User& User::operator=(const User& other)
{
	if (this != &other)
	{
		setUsername(other.m_username);
		setPassword(other.m_password);
		setFname(other.m_fname);
		setLname(other.m_lname);

		m_address = other.m_address;
	}
	return *this;
}

bool User::setPassword(const char* password)
{ // set password for seller. Validation check - not an empty string.
	if (strlen(password) == 0)
		return false;
	m_password = nullptr;
	delete[]m_password;
	m_password = strdup(password);
	return true;
}

bool User::setFname(const char* fname)
{ // set first name for seller. Validation check 
	int i = 0;

	while (fname[i] != '\0' && isLetter(fname[i]))
	{
		i++;
	}
	if (fname[i] != '\0' || i <= 1)
	{
		return false;
	} //We assumed that the fname can be a word with only letters (more than 1 character) 
	m_fname = nullptr;
	delete[]m_fname;
	m_fname = strdup(fname);
	return true;
}

bool User::setLname(const char* lname)
{ // set last name for seller. Validation check 
	int i = 0;

	while (lname[i] != '\0' && (isLetter(lname[i]) || lname[i] == ' '))
	{
		i++;
	}
	if (lname[i] != '\0' || i <= 1)
	{
		return false;
	} //We assumed that the lname can be a word with letters and spaces (more than 1 character) 

	m_lname = nullptr;
	delete[]m_lname;
	m_lname = strdup(lname);
	return true;
}

bool User::setUsername(const char* username) // private - username cannot get changed after initialization 
{  // set username for seller. Validation check - not an empty string.
	if (strlen(username) == 0)
		return false;

	m_username = nullptr;
	delete[]m_username;
	m_username = strdup(username);
	return true;
}

bool User::setAddress(const Address& address) 
{
	m_address = address;
	return true;
}


ostream& operator<<(ostream& os, const User& user)
{
	os << "\tFull name: " << user.m_fname << " " << user.m_lname <<
		"\n\tUsername: " << user.m_username	<< "\n\tAddress: " << user.m_address;
	user.toOs(os);
	return os;
}
