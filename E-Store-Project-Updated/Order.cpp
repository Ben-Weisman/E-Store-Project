#include "Order.h"

Order::Order(unsigned int total_price=0)//:Seller seller(), Buyer Buyer() //?????????????????????????????????????????????? init line 
{
	setTotalPrice(total_price);
	setProductsPhySize(1);
	setNunOfProducts(0);
	
	m_checkout_arr = new Product*[m_products_phy_size]; // is That enough? 
}


Order::~Order()
{
	for (int i = 0; i < m_num_of_products; i++)
		delete m_checkout_arr[i];

	delete m_checkout_arr;
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
bool Order::setNunOfProducts(unsigned int num_of_prod)
{
	m_num_of_products = num_of_prod;
}

// Do we need setters to buyer&seller ?



//////////////////////////////////////////////////////////  getters  ///////////////////////////////////////////////////////////

unsigned int Order::getTotalPrice()const
{
	return m_total_price;
}
unsigned int Order::getProductsPhySize()const
{
	return m_products_phy_size;
}
unsigned int Order::getNunOfProducts()const
{
	return m_num_of_products;
}
const Seller& Order::getSeller()const
{
	return m_seller;
}
const Buyer& Order::getBuyer()const
{
	return m_buyer;
}
Product** Order::getProductsArr()const
{
	return m_checkout_arr;
}
	