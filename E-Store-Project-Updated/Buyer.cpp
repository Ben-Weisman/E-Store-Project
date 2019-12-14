#include "Buyer.h"
#include <iostream>
#include <string>
using namespace std;
inline const int Buyer::getNumberOfItems()const { return m_number_of_items; }
const char* Buyer::getFirstName()const { return m_fname; }
const char* Buyer::getLastName()const { return m_lname; }
const char* Buyer::getUsername()const { return m_username; }
Product** Buyer::getCart()const { return m_cart; }
const Address Buyer::getAddress()const { return m_address; }

////// Moved to Order.h //////

void Buyer::removeFromCart(Product* item_to_delete)
{

	for (int i = 0; i < m_number_of_items; i++)
	{
		if (m_cart[i]->getSerialNumber() == item_to_delete->getSerialNumber)
		{			
			Product* tmp;
			for (int j = i; j < m_number_of_items - 1; j++)
			{
				tmp = m_cart[j];
					m_cart[j] = m_cart[j + 1];
				m_cart[j + 1] = tmp;
			}
			m_cart[m_number_of_items - 1] = nullptr;
			m_number_of_items -= 1;
			break;
		}
	}
}

void Buyer::addToCart(Product* item_to_add)
{ 
	if (m_cartPsize == m_number_of_items)
		cartRealloc();
	m_cart[m_number_of_items++] = item_to_add;
}

void Buyer::addToCheckout(Order* checkout_order)
{
	if (m_num_checkout_orders == m_checkout_orders_pSize)
		checkoutRealloc();
	m_checkout_orders[m_num_checkout_orders++] = checkout_order;
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

Buyer::Buyer(char* userName, char* password, char* fname,
	char* lname, const Address& address):m_address(address) // c'tor
{
	m_username = strdup(userName);
	m_password = strdup(password);
	m_fname = strdup(fname);
	m_lname = strdup(lname);
	m_cart
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

void Buyer::cartRealloc()
{
	this->m_cartPsize *= 2;
	Product** tmp = new Product*[m_cartPsize];

	for (int i = 0; i < m_number_of_items; i++)
		tmp[i] = m_cart[i];
	delete m_cart;

	m_cart = tmp;
}

void Buyer::checkoutRealloc()
{
	m_checkout_orders_pSize *= 2;

	Order** tmp = new Order * [m_checkout_orders_pSize];

	for (int i = 0; i < m_num_checkout_orders; i++)
		tmp[i] = m_checkout_orders[i];
	delete m_checkout_orders;

	m_checkout_orders = tmp;
}