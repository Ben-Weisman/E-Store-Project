#ifndef __Order_h
#define __Order_h

#include "Product.h"

class Buyer; //forword declaration


class Order
{
	Product** m_product_arr;
	int m_product_phy_size;
	int m_num_of_products;
	int m_total_price;
	Seller* const m_seller; // Can't change them pointing
	Buyer* const m_buyer;  // Can't change them pointing
	bool m_paid; // indication - the order already paid or not?
	
	
public:
	Order(Seller* s, Buyer* b);
	~Order();

public:
	inline bool setTotalPrice(int total_price);
	inline bool setProductsPhySize(int phy_size);
	inline bool setNumOfProducts(int num_of_prod);
	inline bool setPaid(bool paid);
public:
	inline unsigned int getTotalPrice()const;
	inline unsigned int getProductsPhySize()const;
	inline unsigned int getNumOfProducts()const;
	inline Seller*const getSeller()const;
	inline Buyer* const  getBuyer()const;
	Product** getProductsArr()const;
	bool getPaid()const;
	
public:
	inline void printOrder()const;
};

#endif //!__Order_h