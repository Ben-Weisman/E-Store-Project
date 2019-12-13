#include "Product.h"
#include <string.h>
#include "utils.h"
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////

int Product::COUNTER = 100000; // First serial number value

////////////////////////////////////////////////////////////////////////////////////////////////////

Product::Product(ecategory category, char* name, int price) : m_serial_number(++COUNTER) //c'tor
{
	setCategory(category);

	setName(name);

	setPrice(price);

}

Product::~Product() //d'tor
{
	delete[]m_name;
}

Product::Product(const Product&p) //copy c'tor
{
	setCategory(p.m_category);

	setName(p.m_name);

	setPrice(p.m_price);

	m_serial_number = p.m_serial_number;
}

Product::Product(Product&&p) //move c'tor
{
	m_category = p.m_category;
	m_name = m_name;
	m_price = p.m_price;
	m_serial_number = p.m_serial_number;

	p.m_name = nullptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////

Product::ecategory Product::getCategory()const
{
	return m_category;
}
const char* Product::getName()const
{
	return m_name;
}
int Product::getPrice()const
{
	return m_price;
}
int Product::getSerialNumber()const
{
	return m_serial_number;
}

//////////////////////////////////////////////////////////////////////////////////////////////

bool Product::setCategory(ecategory category)
{
	if (category <= 3 && category >= 0)
	{
		m_category = category;
		return true;
	}
	return false; //in case that the category is not one from the list of categories
}
bool Product::setName(const char* name)
{
	//check if name=null?
	bool flag = true;
	int i = 0, letter_counter = 0;
	while (flag&&name[i] != '\0') //Check product name validation (2 letters min, no spaces and numbers allowed)
	{
		if ((name[i] >= 'a'&&name[i] <= 'z') || (name[i] >= 'A'&&name[i] <= 'Z'))
			letter_counter++;
		else if (name[i] <= '0' || name[i] >= '9') //Right check?
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
bool Product::setPrice(int price)
{
	if (price > 0)
	{
		m_price = price;
		return true;
	}
	return false; //Nothing free in the world! 
}

//////////////////////////////////////////////////////////////////////////////////////////////

void Product::printProduct() const
{
	cout << "Product name: " << m_name << endl << "category: " << /*category_arr[m_category] <<*/  endl;
	cout << "price: " << m_price << endl << "serial number: " << m_serial_number << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////
