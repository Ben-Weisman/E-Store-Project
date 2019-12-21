#include "Buyer.h"
#include "Seller.h"
#include "Order.h"
#include <iostream>

#pragma warning(disable:4996) 
using namespace std;

// -------------------- C'tor, Copy C'tor, D'tor --------------------
Buyer::Buyer(char* userName, char* password, char* fname,
	char* lname, const Address& address) :m_address(address) // c'tor
{
	cout << endl << "########################################### IN BUYER C'TOR ###########################################"<< endl;

	setUsername(userName);
	setPassword(password);
	setFname(fname);
	setLname(lname);

	m_number_of_items = 0;
	m_cartPsize = 1;
	m_num_checkout_orders = 0;
	m_checkout_orders_pSize = 1;

	m_cart = new Product *[m_cartPsize];
	m_cart[0] = nullptr;
	m_checkout_orders = new Order *[m_checkout_orders_pSize];
	m_checkout_orders[0] = nullptr;


}

Buyer::Buyer(const Buyer& b) :m_address(b.m_address) // copy c'tor
{
	cout << endl << "########################################### IN BUYER COPY ###########################################"<< endl;

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
	cout << endl << "########################################### IN BUYER D'TOR ###########################################"<< endl;

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


//----------------------- Setters Methods -----------------------

bool Buyer::setPassword(const char* password)
{ // Set password for buyer. Validation check - Not an empty string.
	if (strlen(password) == 0)
		return false;
	delete[]m_password;
	m_password = strdup(password);
	return true;
}

bool Buyer::setFname(const char* fname)
{ // Set first name for buyer. Validation check - Not an empty string.
	if (strlen(fname) == 0)
		return false;
	delete[]m_fname;
	m_fname = strdup(fname);
	return true;
}

bool Buyer::setLname(const char* lname)
{ // Set last name for buyer. Validation check - Not an empty string.
	if (strlen(lname) == 0)
		return false;
	delete[]m_lname;
	m_lname = strdup(lname);
	return true;
}

bool Buyer::setUsername(char* username) // Private. initiated username cannot get changed afterwards. 
{ // Set username for buyer. Validation check - Not an empty string.
	if (strlen(username) == 0)
		return false;
	m_username = strdup(username);
	return true;
}

bool Buyer::setCart(Product** cart)
{ // Set cart for buyer. Validation check - cart exists.
	if (!cart)
		return false;
	m_cart = cart;
	return true;
}

bool Buyer::setOrder(Order** order)
{ // Set cart for buyer. Validation check - orders exists.
	if (!order)
		return false;
	m_checkout_orders = order;
	return true;

}


// ----------------------- Buyer's arrays maintenance methods. ----------------------- 

bool Buyer::addToCart(Product* item_to_add)
{ // Add to buyer's cart using realloc method.
	if (m_cartPsize == m_number_of_items)
		cartRealloc();
	m_cart[m_number_of_items++] = item_to_add;
	return true;
}

void Buyer::addToCheckout(Order* checkout_order)
{ // Add to Buyer's checkout cart using realloc method.
	if (m_num_checkout_orders == m_checkout_orders_pSize)
		checkoutRealloc();
	m_checkout_orders[m_num_checkout_orders++] = checkout_order;
}

void Buyer::removeFromCart(Product* item_to_delete)
{ // Remove a product from buyer's cart by bubbling it to the end of the arr, and setting it to nullptr.

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

void Buyer::cartRealloc()
{ // Resize cart.
	this->m_cartPsize *= 2;
	Product** tmp = new Product *[m_cartPsize];

	for (int i = 0; i < m_number_of_items; i++)
		tmp[i] = m_cart[i];
	delete m_cart;

	m_cart = tmp;
}

void Buyer::checkoutRealloc()
{ // Resize checkout arr.
	m_checkout_orders_pSize *= 2;

	Order** tmp = new Order *[m_checkout_orders_pSize];

	for (int i = 0; i < m_num_checkout_orders; i++)
		tmp[i] = m_checkout_orders[i];
	delete m_checkout_orders;

	m_checkout_orders = tmp;
}


// ----------------------- Printing methods. -----------------------

void Buyer::showCart()const
{ // Print buyer's cart.

	if (m_number_of_items == 0)
		cout << endl << "No products to show, your cart is currently empty." << endl <<
		"Please search for products to buy or go to your checkout cart to continue with your order" << endl;
	else{
		cout << "All products are in #/Name/Price/Seller format" << endl;
	
		for (int i = 0; i < m_number_of_items; i++)
			cout << i + 1 << ") " << this->m_cart[i]->getName() << "\t" << this->m_cart[i]->getPrice() <<
			"$\t" << this->m_cart[i]->getSellerUsername() << endl;
	}
}

void Buyer::showBuyer()const
{ // Print buyer's info.
	cout << "Full Name: " << this->getFirstName() << " " << this->getLastName() << endl;
	cout << "Username: " << this->getUsername() << endl;
	cout << "From: " << this->getAddress().getCountry() << endl;
}

void Buyer::showCheckoutOrders()const
{ // Show all orders that hasn't been paid yet.
	for (int i = 0; i < m_num_checkout_orders; i++)
	{
		if (!this->m_checkout_orders[i]->getPaid())
		{
			cout << "\t Order #" << i + 1 << endl;
			this->m_checkout_orders[i]->showOrder();
		}
	}
}

// ---------------------------------------------------------------------

bool Buyer::isOrderedFrom(const char* username)const
{ // Check if there's an existing order from a given seller, and that it's paid for.
	for (int i = 0; i < this->m_num_checkout_orders; i++)
	{
		for (int j = 0; j < m_checkout_orders[i]->getNumOfProducts(); j++)
		{
			if (strcmp(this->m_checkout_orders[i]->getProductsArr()[j]->getSellerUsername(), username) == 0)
			{
				if (this->m_checkout_orders[i]->getPaid())
					return true;
			}
		}
	}
	return false;
}

bool Buyer::isEmptyCheckoutOrders()
{
	if (m_num_checkout_orders == 0)
		return true;
	return false;
}