#ifndef __Product_h
#define __Product_h

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
	char* m_name;
	double m_price;
	int m_serial_number;
	char* m_seller_username;

public:
	Product(ecategory category, char* name, double price, char* seller_username); //c'tor
	~Product(); //d'tor
	Product(const Product&p); //copy c'tor
	Product(Product&&p); //move c'tor

public:
	friend ostream& operator<<(ostream& os, const Product& product);

public:
	bool setName(const char* name);
	 bool setPrice(double price);

private:
	 bool setCategory(ecategory category); //we didn't give the option to change the category
	bool setSellerUsername(char* seller_username); //we didn't give the option to change the product seller's username

public:
	inline ecategory getCategory()const { return m_category; }
	inline const char* getName()const{ return m_name; }
	inline double getPrice()const{ return m_price; }
	inline int getSerialNumber()const{ return m_serial_number; }
	inline const char* getSellerUsername()const{ return m_seller_username; }


public:
	//void showProduct()const; # transfer that func to << operator
	void showProductToBuyer()const;
};
#endif // !__Product_h
