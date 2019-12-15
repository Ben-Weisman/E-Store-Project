#ifndef __Product_h
#define __Product_h

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
	int m_price;
	int m_serial_number;
	char* m_seller_username; 

public:
	Product(ecategory category, char* name, int price, char* seller_username); //c'tor
	~Product(); //d'tor
	Product(const Product&p); //copy c'tor
	Product(Product&&p); //move c'tor

public:
	inline bool setCategory(ecategory category);
	bool setName(const char* name);
	inline bool setPrice(int price);

private:
	bool setSellerUsername(char* seller_username); //we didn't give the option to change the product seller's username

public:
	inline ecategory getCategory()const;
	inline const char* getName()const;
	inline int getPrice()const;
	inline int getSerialNumber()const;
	inline int getSerialNumber()const;
	inline const char* getSellerUsername()const;


public:
	inline void printProduct()const;
};
#endif // !__Product_h
