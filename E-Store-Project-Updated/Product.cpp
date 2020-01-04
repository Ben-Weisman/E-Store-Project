#include "Product.h"
#include "Utils.h"
#include <string.h>

#pragma warning(disable:4996) 

// --------------------- static ---------------------

int Product::COUNTER = 100000; // First serial number value

// --------------------- C'tor, Copy C'tor, D'tor, Move C'tor ---------------------


Product::Product(ecategory category, char* name, double price, char* seller_username) :m_serial_number(++COUNTER) //c'tor
{
	setCategory(category);
	setName(name);
	setPrice(price);
	setSellerUsername(seller_username);
}

Product::~Product() //d'tor
{
	delete[]m_name;
	delete[]m_seller_username;
}

Product::Product(const Product&p) :m_serial_number(p.m_serial_number) //copy c'tor
{
	setCategory(p.m_category);

	setName(p.m_name);

	setPrice(p.m_price);

	setSellerUsername(p.m_seller_username);
}

Product::Product(Product&&p) : m_serial_number(std::move(p.m_serial_number)) //move c'tor
{
	m_category = p.m_category;
	m_name = m_name;
	m_price = p.m_price;
	m_seller_username = p.m_seller_username;

	p.m_name = nullptr;
	p.m_seller_username = nullptr;
}

// ---------------------------------- operators ------------------------------------------


ostream& operator<<(ostream& os, const Product& product)
{ 
    os << endl << "\tProduct name: " << product.m_name << endl << "\tcategory: " << product.CATEGORY_ARR[product.m_category] << endl;
	os << "\tprice: " << product.m_price << "$" << endl << "\tserial number: " << product.m_serial_number << endl;
	os << "\tThe seller of this product is: " << product.m_seller_username << endl;
	
	return os;
}

// ---------------------------------- public setters ------------------------------------------



bool Product::setName(const char* name)
{ //Check product name validation (2 letters min, no spaces and numbers allowed)
	bool flag = true;
	int i = 0, letter_counter = 0;
	while (flag&&name[i] != '\0') 
	{
		if ((name[i] >= 'a'&&name[i] <= 'z') || (name[i] >= 'A'&&name[i] <= 'Z'))
			letter_counter++;
		else if (name[i] <= '0' || name[i] >= '9') 
			flag = false;

		i++;
	}

	if (flag&&letter_counter >= 2) //name is valid
	{
		delete[] m_name; //in case that user change product name
		m_name = strdup(name);
	}
	return flag;
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

bool Product::setSellerUsername(char* seller_username) //private method that we used only once at the c'tor 
{
	m_seller_username = strdup(seller_username);
	return true;

}



// ----------------------- Printing methods -----------------------

void Product::showProductToBuyer()const
{
	cout << endl << "\tProduct name: " << m_name << endl;
	cout << "\tprice: " << m_price << "$" << endl;
	cout << "\tThe seller of this product is: " << m_seller_username << endl;
}




