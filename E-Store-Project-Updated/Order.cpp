#include "Order.h"
#include <iostream>
using namespace std;

Order::Order(Buyer* b) :m_buyer(b) // Aviv ??????????????????????????????????????????????????????????????????????????????????????????????????????
{
	setTotalPrice(m_total_price);
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



//////////////////////////////////////////////////////////  setters  ///////////////////////////////////////////////////////////

bool Order::setTotalPrice(int total_price)
{
	m_total_price = total_price;
	return true; // unsigned - so can't be negative price
}
bool Order::setProductsPhySize(int phy_size)
{
	m_products_phy_size = phy_size;
}
bool Order::setNumOfProducts(int num_of_prod)
{
	m_num_of_products = num_of_prod;
}
bool Order::setPaid(bool paid)
{
	m_paid = paid;
}




//////////////////////////////////////////////////////////  getters  ///////////////////////////////////////////////////////////

unsigned int Order::getTotalPrice()const
{
	return m_total_price;
}
unsigned int Order::getProductsPhySize()const
{
	return m_products_phy_size;
}
unsigned int Order::getNumOfProducts()const
{
	return m_num_of_products;
}
Buyer* const  Order::getBuyer()const
{
	return m_buyer;
}
Product** Order::getProductsArr()const
{
	return m_products_arr;
}
bool Order::getPaid()const
{
	return m_paid;
}
	
/////////////////////////////////////////////////////////////////////// functions ////////////////////////////////////////////////////////////////////////////
void Order::showOrder()const
{
	for (int i = 0; i < m_num_of_products; i++)
	{
		cout << i + 1 << ") " << m_products_arr[i]->getName() << endl;
	}
	cout << m_total_price << endl;
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