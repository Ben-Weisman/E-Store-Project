#ifndef __Product_h
#define __Product_h

#include <string>
#include <iostream>
using namespace std;

class Product
{
public:
	enum ecategory { Kids, Electricity, Office, Clothing };
	static constexpr const char* CATEGORY_ARR[] = { "Kids", "Electricity", "Office", "Clothing" };

private:
	static int COUNTER; // assist for the serial number

private:
	ecategory m_category;
	string m_name;
	double m_price;
	int m_serial_number;
	string m_seller_username;

public:
	Product(ecategory category, const string& name, double price, const string& seller_username); //c'tor
	~Product(); //d'tor
	Product(Product&&p); //move c'tor
private:
	Product(const Product&p); //copy c'tor
	const Product& operator=(const Product& p);

public:
	friend ostream& operator<<(ostream& os, const Product& product);


public:
	bool setName(const string& name);
	 bool setPrice(double price);

private:
	 bool setCategory(ecategory category); //we didn't give the option to change the category
	bool setSellerUsername(const string& seller_username); //we didn't give the option to change the product seller's username

public:
	inline ecategory getCategory()const { return m_category; }
	inline const string& getName()const{ return m_name; }
	inline double getPrice()const{ return m_price; }
	inline int getSerialNumber()const{ return m_serial_number; }
	inline const string& getSellerUsername()const{ return m_seller_username; }


public:
	void showProductToBuyer()const;

	friend class System;
	friend class Order;
};
#endif // !__Product_h
