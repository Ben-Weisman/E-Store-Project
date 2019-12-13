#include "Order.h"

Order::Order(Seller* s, Buyer* b) :m_seller(s), m_buyer(b)
{
	setTotalPrice(m_total_price);
	setProductsPhySize(1);
	setNumOfProducts(0);
	setTotalPrice(0);
	setPaid(false);
	
	m_wishlist_arr = new Product*[m_products_phy_size]; // is That enough? 
}


Order::~Order()
{
	for (int i = 0; i < m_num_of_products; i++)
		delete m_wishlist_arr[i];

	delete m_wishlist_arr;
}



//////////////////////////////////////////////////////////  setters  ///////////////////////////////////////////////////////////

bool Order::setTotalPrice(unsigned int total_price)
{
	m_total_price = total_price;
	return true; // unsigned - so can't be negative price
}
bool Order::setProductsPhySize(unsigned int phy_size)
{
	m_products_phy_size = phy_size;
}
bool Order::setNumOfProducts(unsigned int num_of_prod)
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
 Seller* const Order::getSeller()const
{
	return m_seller;
}
Buyer* const  Order::getBuyer()const
{
	return m_buyer;
}
Product** Order::getProductsArr()const
{
	return m_wishlist_arr;
}
bool Order::getPaid()const
{
	return m_paid;
}
	