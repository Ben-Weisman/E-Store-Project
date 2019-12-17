#ifndef __Order_h
#define __Order_h

#include "Product.h"
#include "Buyer.h"

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
	inline bool setTotalPrice(int total_price);
	inline bool setPaid(bool paid);
private:
	inline bool setProductsPhySize(int phy_size);
	inline bool setNumOfProducts(int num_of_prod);

public:
	inline int getTotalPrice()const;
	inline int getProductsPhySize()const;
	inline int getNumOfProducts()const;
	inline Buyer* const  getBuyer()const;
	Product** getProductsArr()const;
	bool getPaid()const;

public:
	inline void showOrder()const;
	void addToProdArr(Product* p);
	void productsRealloc();

};

#endif //!__Order_h