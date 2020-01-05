#include "Order.h"
#include "Buyer.h"

#include <iostream>
using namespace std;

// ----------------------------------------- c'tor & d'tor ---------------------------------


Order::Order(Buyer* b) :m_buyer(b)
{
	setProductsPhySize(1);
	setNumOfProducts(0);
	setTotalPrice(0);
	setPaid(false);

	m_products_arr = new Product*[m_products_phy_size];
}


Order::~Order()
{
	for (int i = 0; i < m_num_of_products; i++)
		delete m_products_arr[i];

	delete m_products_arr;
}

Order::Order(const Order& o):m_buyer(o.m_buyer)
{
	*this = o;
}


// ----------------------------------------- operators ---------------------------------

const Order& Order::operator=(const Order& o) 
{
	if (this != &o)
	{
		setTotalPrice(o.m_total_price);
		setProductsPhySize(o.m_products_phy_size);
		setNumOfProducts(o.m_num_of_products);
		setPaid(false);
		//# Nir: what about the buyer pointer ? 

		m_products_arr = new Product*[m_products_phy_size];
		for (int i = 0; i < m_num_of_products; i++)
		{
			m_products_arr[i] = o.m_products_arr[i]; // use product = operator
		}
	}
	return *this;
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
bool Order::setProductsPhySize(int phy_size)
{
	m_products_phy_size = phy_size;
	return true;
}
bool Order::setNumOfProducts(int num_of_prod)
{
	m_num_of_products = num_of_prod;
	return true;
}
bool Order::setPaid(bool paid)
{
	m_paid = paid;
	return true;
}


// ----------------------------------------- printing methods ---------------------------------

void Order::showOrder()const
{
	for (int i = 0; i < m_num_of_products; i++)
	{
		cout << i + 1 << ") " << endl <<"\t"<< m_products_arr[i]->getName() << endl;
	}
	cout << "\tTotal Price of the order: " <<m_total_price << "$" << endl;
}


// ----------------------------------------- more functions ---------------------------------

void Order::addToProdArr(Product* p)
{
	if (m_num_of_products == m_products_phy_size)
		productsRealloc();
	m_products_arr[m_num_of_products++] = p;

	m_buyer->removeFromCart(p);
	m_total_price += p->getPrice();
}

void Order::productsRealloc()
{
	this->m_products_phy_size *= 2;
	Product** tmp = new Product *[m_products_phy_size];

	for (int i = 0; i < m_num_of_products; i++)
		tmp[i] = m_products_arr[i];
	delete m_products_arr;

	m_products_arr = tmp;
}