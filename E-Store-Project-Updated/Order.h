#ifndef __Order_h
#define __Order_h

#include "Product.h"

class Buyer; //forword declaration

class Order
{
	Product** m_products_arr;
	int m_products_phy_size;
	int m_num_of_products;
	double m_total_price;
	Buyer* const m_buyer;  // Can't change buyer
	bool m_paid; // indication - the order already paid or not

private:
	Order(const Order& o); 
	const Order& operator=(const Order& o);

public:
	Order(Buyer* b);
	~Order();

public:

	 bool setTotalPrice(double total_price);
	 bool setPaid(bool paid);
private:
	 bool setProductsPhySize(int phy_size);
	 bool setNumOfProducts(int num_of_prod);

public:

	inline double getTotalPrice()const{ return m_total_price; }
	inline  int getProductsPhySize()const{ return m_products_phy_size; }
	inline int getNumOfProducts()const{ return m_num_of_products; }
	inline  Buyer* const  getBuyer()const{ return m_buyer; }
	inline Product** getProductsArr()const { return m_products_arr; }
	inline 	bool getPaid()const{ return m_paid; }

public:

	void showOrder()const;
	void addToProdArr(Product* p);
	void productsRealloc();

};

#endif //!__Order_h