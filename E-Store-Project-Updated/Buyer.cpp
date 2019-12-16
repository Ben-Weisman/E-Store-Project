#include "Buyer.h"
#include "Seller.h"
#include "Order.h"
#include <iostream>
#include <string>
#pragma warning(disable:4996) 
using namespace std;


inline const int Buyer::getNumberOfItems()const { return m_number_of_items; }
const char* Buyer::getFirstName()const { return m_fname; }
const char* Buyer::getLastName()const { return m_lname; }
const char* Buyer::getUsername()const { return m_username; }
Product** Buyer::getCart()const { return m_cart; }
const Address Buyer::getAddress()const { return m_address; }
inline Order** Buyer::getOrders()const { return m_checkout_orders; }

void Buyer::removeFromCart(Product* item_to_delete)
{

	for (int i = 0; i < m_number_of_items; i++)
	{
		if (m_cart[i]->getSerialNumber() == item_to_delete->getSerialNumber())
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

void Buyer::showCart()const
{
	cout << "All products are in #/Name/Price/Seller format" << endl;

	for (int i = 0; i < m_number_of_items; i++)
		cout << i + 1 << ") " << m_cart[i]->getName() << m_cart[i]->getPrice() <<
		m_cart[i]->getSellerUsername() << endl;
}

void Buyer::addToCart(Product* item_to_add)
{ 
	if (m_cartPsize == m_number_of_items)
		cartRealloc();
	m_cart[m_number_of_items++] = item_to_add;
}

void Buyer::addToCheckout(Order* checkout_order, int cart_index)
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

bool Buyer::setUsername(char* username)
{
	if (strlen(username) == 0)
		return false;
	m_username = strdup(username);
	return true;
}

bool Buyer::setCart(Product** cart)
{
	if (!cart)
		return false;
	m_cart = cart;
	return true;
}

bool Buyer::setOrder(Order* order)
{
	if (!order)
		return false;

}

Buyer::Buyer(char* userName, char* password, char* fname,
	char* lname, const Address& address):m_address(address) // c'tor
{
	setUsername(userName);
	setPassword(password);
	setFname(fname);
	setLname(lname);

	m_number_of_items = 0;
	m_cartPsize = 1;
	m_num_checkout_orders = 0;
	m_checkout_orders_pSize = 1;

	m_cart = new Product * [m_cartPsize];
	m_cart[0] = nullptr;
	m_checkout_orders = new Order * [m_checkout_orders_pSize];
	m_checkout_orders[0] = nullptr;


}

Buyer::Buyer(const Buyer& b):m_address(b.m_address) // copy c'tor
{
	setUsername(b.m_username);
	setPassword(b.m_password);
	setFname(b.m_fname);
	setLname(b.m_lname);
	setCart(b.m_cart);
	setOrder(b.getOrders());

	m_cartPsize = b.m_cartPsize;
	m_number_of_items = b.m_number_of_items;
	m_num_checkout_orders = b.m_num_checkout_orders;
	m_checkout_orders_pSize = b.m_checkout_orders_pSize;
}

Buyer::~Buyer() // d'tor
{
	int i;
	delete[]m_fname;
	delete[]m_lname;
	delete[]m_username;
	delete[]m_password;
	
	
	for (i = 0; i < m_number_of_items; i++)
		delete m_cart[i];
	for (i = 0; i < m_num_checkout_orders; i++)
		delete m_checkout_orders[i];
}

void Buyer::showBuyer()const
{
	cout << "Full Name: " << this->getFirstName() << " " << this->getLastName() << endl;
	cout << "Username: " << this->getUsername();
	this->getAddress().showAddress();
	//cout << "Address: "<< endl << this->getAddress().printAddress() << endl;


	for (int i = 0; i < m_number_of_items; i++)
		m_cart[i]->showProduct();

}

void Buyer::showCheckoutOrders()const
{
	for (int i = 0; i < m_num_checkout_orders; i++)
		m_checkout_orders[i]->showOrder();
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