#include "Buyer.h"
#include "Utils.h"
#include "Seller.h"
#include "Order.h"
#include <iostream>
#include <typeinfo>
#pragma warning(disable:4996) 

using namespace std;

// -------------------- C'tor, Copy C'tor, D'tor --------------------
Buyer::Buyer(const char* userName,const char* password, const char* fname,
	const char* lname, const Address& address): User(userName, password, fname, lname, address)
{
	m_number_of_items = 0;
	m_cartPsize = 1;
	m_num_checkout_orders = 0;
	m_checkout_orders_pSize = 1;

	m_cart = new Product *[m_cartPsize];
	m_cart[0] = nullptr;
	m_checkout_orders = new Order *[m_checkout_orders_pSize];
	m_checkout_orders[0] = nullptr;
}

Buyer::Buyer(const Buyer& b): User(b) // copy c'tor
{
	*this = b;
}

Buyer::~Buyer() // d'tor
{
	for (int i = 0; i < m_number_of_items; i++)
		delete m_cart[i];
	for (int i = 0; i < m_num_checkout_orders; i++)
		delete m_checkout_orders[i];
}


//----------------------- Setters Methods -----------------------

bool Buyer::setCart(Product** cart)
{ // Set cart for buyer. Validation check - cart exists.
	if (!cart)
		return false;
	m_cart = cart;
	return true;
}

bool Buyer::setOrders(Order** other) // private - Orders cannot get changed after initialization
{  // set orders for seller. Validation check - pointer exists.
	if (!other)
		return false;
	m_checkout_orders = other;
	return true;
}


// ----------------------- Buyer's arrays maintenance methods. ----------------------- 

bool Buyer::addToCart(Product* item_to_add)
{ // Add to buyer's cart using realloc method.
	if (!item_to_add)
		return false;
	if (m_cartPsize == m_number_of_items)
		cartRealloc();
	m_cart[m_number_of_items++] = item_to_add;
	return true;
}

bool Buyer::addToCheckout(Order* checkout_order)
{ // Add to Buyer's checkout cart using realloc method.
	if (!checkout_order)
		return false;
	if (m_num_checkout_orders == m_checkout_orders_pSize)
		checkoutRealloc();
	m_checkout_orders[m_num_checkout_orders++] = checkout_order;
	return true;
}

bool Buyer::removeFromCart(Product* item_to_delete)
{ /* Remove a product from buyer's cart by bubbling it to the end of the arr,
	and setting it to nullptr.*/
	bool flag = false;
	for (int i = 0; i < m_number_of_items; i++)
	{
		if (m_cart[i]->getSerialNumber() == item_to_delete->getSerialNumber())
		{
			flag = true;
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
	return flag;
}

void Buyer::cartRealloc()
{ // Resize cart.
	m_cartPsize *= 2;
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
			cout << i + 1 << ") " << m_cart[i]->getName() << "\t" << m_cart[i]->getPrice() <<
			"$\t" << m_cart[i]->getSellerUsername() << endl;
	}
}

void Buyer::showBuyer()const
{ // Print buyer's info.
	cout << "\tFull Name: " << m_fname << " " << m_lname << endl;
	cout << "\tUsername: " << m_username << endl;
	cout << "\tFrom: " << m_address.getCountry() << endl;
}

void Buyer::showCheckoutOrders()const
{ // Show all orders that hasn't been paid yet.
	for (int i = 0; i < m_num_checkout_orders; i++)
	{
		if (!this->m_checkout_orders[i]->getPaid())
		{
			cout << "\n\t Order #" << i + 1 << endl;
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
{ //  Is empty even if there are actual orders in the arr, but they're all paid for. 
	for (int i = 0; i < this->getNumOfOrders(); i++)
	{
		if (!this->getBuyerOrders()[i]->getPaid())
			return false;
	}
	return true;
}

int const Buyer::getTotalCartValue()const
{ 
	int res = 0;

	for (int i = 0; i < this->getNumberOfItems(); i++)
		res +=(int)this->m_cart[i]->getPrice();
	for (int i = 0; i < this->getNumOfOrders(); i++)
	{
		if (!this->m_checkout_orders[i]->getPaid())
		{
			for (int j = 0; j < this->m_checkout_orders[i]->getNumOfProducts(); j++)
				res += (int)this->m_checkout_orders[i]->getProductsArr()[j]->getPrice();
		}
	}
	return res;
}

bool Buyer::isEmptyCart()
{
	if (this->m_number_of_items == 0)
		return true;
	return false;
}

bool Buyer::operator>(const Buyer& other)const
{
	return this->getTotalCartValue() > other.getTotalCartValue(); 
}

const Buyer& Buyer::operator=(const Buyer& other)
{ 
	if (this != &other)
	{
		User::operator=(other);

		m_cartPsize = other.m_cartPsize;
		m_number_of_items = other.m_number_of_items;
		m_num_checkout_orders = other.m_num_checkout_orders;
		m_checkout_orders_pSize = other.m_checkout_orders_pSize;

		m_cart = new Product *[m_cartPsize];
		m_checkout_orders = new Order * [m_checkout_orders_pSize];

		for (int i = 0; i < m_number_of_items; i++)
			*(m_cart+i) = *(other.m_cart+i);
		for (int i = 0; i < m_num_checkout_orders; i++)
			*(m_checkout_orders+i) = *(other.m_checkout_orders+i);

	}
	return *this;

}
 void Buyer::toOs(ostream& os)const
{
	 os << typeid(*this).name() + 6;

}

