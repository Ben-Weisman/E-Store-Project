#include "Buyer.h"
#include <iostream>
#include <string>
using namespace std;
inline const int Buyer::getNumberOfItems()const { return m_number_of_items; }
const char* Buyer::getFirstName()const { return m_fname; }
const char* Buyer::getLastName()const { return m_lname; }
const char* Buyer::getUsername()const { return m_username; }
const Product** Buyer::getCart()const { return m_cart; }
const Address* Buyer::getAddress()const { return m_address; }

////// Moved to Order.h //////
/*
void Buyer::deleteProductFromCart(Product* item_to_delete)
{ // Verify logic

	for (int i = 0; i < m_number_of_items; i++)
	{
		if (m_cart[i]->getSerialNumber() == item_to_delete->getSerialNumber)
		{ // is it delete or just moving the product by ref to orders?
		// (will be performed by Orders if so)
			i++;
			delete m_cart[i];
			
			Product* tmp;
			for (int j = i; j < m_number_of_items - 1; j++)
			{
				tmp = m_cart[j]
					m_cart[j] = m_cart[j + 1];
				m_cart[j + 1] = tmp;
			}
			delete m_cart[size - 1];
			m_cart[size - 1] = nullptr;
			break;
			
		}
		if (m_number_of_items == m_cartPsize)
		{
			reallocateCart();
		}
	}
}
*/
void Buyer::addToCart(Product* item_to_add)
{ 
	if (m_cartPsize == m_number_of_items)
		reallocateCart();
	m_cart[m_number_of_items++] = item_to_add;
}

bool Buyer::setUserName(const char* username)
{
	if (strlen(username) == 0)
		return false;
	delete[] m_username;
	m_username = strdup(username);
	return true;
}

bool Buyer::setPassword(const char* password)
{
	if (strlen(password) == 0)
		return false;
	delete[]m_password;
	m_password = strdup(password);
	return true;
}

bool Buyer::setFname(const char* fname)
{
	if (strlen(fname) == 0)
		return false;
	delete []m_fname;
	m_fname = strdup(fname);
	return true;
}

bool Buyer::setLname(const char* lname)
{
	if (strlen(lname) == 0)
		return false;
	delete[]m_lname;
	m_lname = strdup(lname);
	return true;
}

bool Buyer::setAddress(const Address* address)
{
	if (!address)
		return false;
	m_address = address;
	return true;
}

bool Buyer::setCart(const Product** cart)
{
	if (!cart)
		return false;
	m_cart = cart;
	return true;
}

Buyer::Buyer(char* userName, char* password, char* fname, char* lname, Address* address, Product** cart) // c'tor
{
	m_username = strdup(userName);
	m_password = strdup(password);
	m_fname = strdup(fname);
	m_lname = strdup(lname);
	setAddress(address);
	setCart(cart);
	m_number_of_items = 0;
	m_cartPsize = 1;
}

Buyer::Buyer(const Buyer& p) // copy c'tor
{
	setUserName(p.m_username);
	setPassword(p.m_password);
	setFname(p.m_fname);
	setLname(p.m_lname);
	setAddress(p.m_address);
	setCart(p.m_cart);
}

Buyer::~Buyer() // d'tor
{
	delete[]m_fname;
	delete[]m_lname;
	delete[]m_username;
	delete[]m_password;
	delete m_address;

	for (int i = 0; i < m_number_of_items; i++)
		delete[]m_cart[i];
}

void Buyer::printBuyer()const
{
	cout << "Name: " << m_fname << " " << m_lname << endl << "Username: " << m_username << endl
		<< "Password: " << m_password << endl << "Address: " << m_address->printAddress << endl
		<< "Shopping Cart: "<< endl;

	for (int i = 0; i < m_number_of_items; i++)
		cout << m_cart[i]->printProduct << endl;

}

void Buyer::reallocateCart()
{
	this->m_cartPsize *= 2;
	Product** tmp = new Product*[m_cartPsize];
	for (int i = 0; i < m_number_of_items; i++)
		tmp[i] = m_cart[i];
	delete []m_cart;

	m_cart = tmp;
}