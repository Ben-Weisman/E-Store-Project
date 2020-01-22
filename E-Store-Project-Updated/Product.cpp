#include "Product.h"
#include "Utils.h"
#include <string.h>

#pragma warning(disable:4996) 

// --------------------- static ---------------------

int Product::COUNTER = 100000; // First serial number value

// --------------------- C'tor, Copy C'tor, D'tor, Move C'tor ---------------------


Product::Product(ecategory category, const string& name, double price, const string& seller_username) :m_serial_number(++COUNTER) //c'tor
{
	setCategory(category);
	setName(name);
	setPrice(price);
	setSellerUsername(seller_username);
}

Product::~Product() //d'tor
{
}

Product::Product(const Product&p)  //copy c'tor
{
	*this = p; //using = operator
}

Product::Product(Product&&p) : m_serial_number(std::move(p.m_serial_number)) //move c'tor
{
	//@@ move() ??@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	m_category = p.m_category;
	m_name = move(m_name);
	m_price = p.m_price;
	m_seller_username = move(p.m_seller_username);

	p.m_name = nullptr;
	p.m_seller_username = nullptr;
}

// ---------------------------------- operators ------------------------------------------

const Product& Product::operator=(const Product& p)
{
	if (this != &p)
	{ 
		setCategory(p.m_category);

		setName(p.m_name);

		setPrice(p.m_price);

		setSellerUsername(p.m_seller_username);

		m_serial_number = p.m_serial_number; 
	}
	return *this;
}

ostream& operator<<(ostream& os, const Product& product)
{ 
    os << endl << "\tProduct name: " << product.m_name << endl << "\tcategory: " << product.CATEGORY_ARR[product.m_category] << endl;
	os << "\tprice: " << product.m_price << "$" << endl << "\tserial number: " << product.m_serial_number << endl;
	os << "\tThe seller of this product is: " << product.m_seller_username << endl;
	
	return os;
}

// ---------------------------------- public setters ------------------------------------------



bool Product::setName(const string& name)
{
	if (name.length() < 3)// Validity check
		return false; //We assumed that the name should be word with more then 2 letters

	m_name = name;
	return true;
}
bool Product::setPrice(double price)
{//validity check
	if (price > 0)
	{
		m_price = price;
		return true;
	}
	return false; //Nothing free in the world! 
}

// ---------------------------------- private setters ------------------------------------------


bool Product::setCategory(ecategory category) //private method that we used only once at the c'tor 
{//validity check
	if (category <= 3 && category >= 0)
	{
		m_category = category;
		return true;
	}
	return false; //in case that the category is not one from the list of categories
}

bool Product::setSellerUsername(const string& seller_username) //private method that we use only once at the c'tor 
{
	if (seller_username.length() < 3)// Validity check
		return false; //We assumed that the name should be word with more then 2 letters

	m_seller_username = seller_username;
	return true;
}


// ----------------------- Printing methods -----------------------

void Product::showProductToBuyer()const
{
	cout << endl << "\tProduct name: " << m_name << endl;
	cout << "\tprice: " << m_price << "$" << endl;
	cout << "\tThe seller of this product is: " << m_seller_username << endl;
}
