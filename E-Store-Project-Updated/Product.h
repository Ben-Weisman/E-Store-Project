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

public:
	Product(ecategory category, char* name, int price); //c'tor
	~Product(); //d'tor
	Product(const Product&p); //copy c'tor
	Product(Product&&p); //move c'tor

public:
	inline bool setCategory(ecategory category);
	bool setName(const char* name);
	inline bool setPrice(int price);

public:
	inline ecategory getCategory()const;
	inline const char* getName()const;
	inline int getPrice()const;
	inline int getSerialNumber()const;

public:
	inline void printProduct()const;
};
#endif // !__Product_h
