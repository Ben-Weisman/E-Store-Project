#ifndef __Order_h
#define __Order_h

#include "Product.h"
#include <vector>

class Buyer; //forword declaration

class Order
{
	vector<Product*> m_products_arr;
	double m_total_price;
	Buyer* const m_buyer;  // Can't change buyer - const pointer
	bool m_paid; // indication - the order already paid or not

private:
	Order(const Order& o); 

public:
	Order(Buyer* b);
	~Order();

public:

	 bool setTotalPrice(double total_price);
	 bool setPaid(bool paid);

public:

	inline double getTotalPrice()const{ return m_total_price; }
	inline  Buyer* const  getBuyer()const{ return m_buyer; }
	inline vector<Product*> getProductsArr()const { return m_products_arr; }
	inline 	bool getPaid()const{ return m_paid; }

public:

	void showOrder()const;
	void addToProdArr(Product* p);


	friend class Seller;
	friend class Buyer;
};

#endif //!__Order_h