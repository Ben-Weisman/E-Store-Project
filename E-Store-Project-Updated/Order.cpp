#include "Order.h"
#include "Buyer.h"

#include <iostream>
using namespace std;

// ----------------------------------------- c'tor & d'tor ---------------------------------


Order::Order(Buyer* b) :m_buyer(b)
{
	setTotalPrice(0);
	setPaid(false);
}

Order::~Order()
{
	for (auto product_ptr : m_products_arr)
		delete product_ptr;
}

Order::Order(const Order& other):m_buyer(other.m_buyer)
{
	setTotalPrice(other.m_total_price);
	setPaid(false);

	for (auto product_ptr : other.m_products_arr)
		m_products_arr.push_back(new Product(*product_ptr));//copy c'tor of survivor
}

// ----------------------------------------- setters ---------------------------------

bool Order::setTotalPrice(double total_price)
{
	if (total_price > 0) // Validity check
	{
		m_total_price = total_price;
		return true;
	}
	return false;
}
bool Order::setPaid(bool paid)
{
	m_paid = paid;
	return true;
}

// ----------------------------------------- printing methods ---------------------------------

void Order::showOrder()const
{
	for (int i = 0; i < m_products_arr.size(); i++)
	{
		cout << i + 1 << ") " << endl <<"\t"<< m_products_arr[i]->getName() << endl;
	}
	cout << "\tTotal Price of the order: " <<m_total_price << "$" << endl;
}


// ----------------------------------------- more functions ---------------------------------

void Order::addToProdArr(Product* p)
{
	m_products_arr.push_back(p); // add the product to the array
	m_buyer->removeFromCart(p); // remove the poduct from the cart - we assumed that what you order not in your cart anymore
	m_total_price += p->getPrice(); // Add the product price to the total price
}