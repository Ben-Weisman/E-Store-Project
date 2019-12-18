#ifndef __Order_h
#define __Order_h

#include "Product.h"

class Buyer; //forword declaration

class Order
{
	Product** m_products_arr;
	int m_products_phy_size;
	int m_num_of_products;
	int m_total_price;
	Buyer* const m_buyer;  // Can't change them pointing
	bool m_paid; // indication - the order already paid or not

private:
	Order(const Order& o); // We don't want to anable copys of products

public:
	Order(Buyer* b);
	~Order();

public:
	 bool setTotalPrice(int total_price);
	 bool setPaid(bool paid);
private:
	 bool setProductsPhySize(int phy_size);
	 bool setNumOfProducts(int num_of_prod);

public:
	 int getTotalPrice()const;
	 int getProductsPhySize()const;
	int getNumOfProducts()const;
	 Buyer* const  getBuyer()const;
	Product** getProductsArr()const;
	bool getPaid()const;

public:
	void showOrder()const;
	void addToProdArr(Product* p);
	void productsRealloc();

};

#endif //!__Order_h