#ifndef __Order_h
#define __Order_h

#include "Product.h"

class Seller; //forword declaration
class Buyer; //forword declaration


class Order
{
	Product** m_wishlist_arr;
	unsigned int m_wishlist_phy_size;
	unsigned int m_num_of_products;
	unsigned int m_total_price;
	Seller* const m_seller; // Can't change them pointing
	Buyer* const m_buyer;  // Can't change them pointing
	bool m_paid; // indication - the order already paid or not?
	
	
public:
	Order(Seller* s, Buyer* b);
	~Order();

public:
	inline bool setTotalPrice(unsigned int total_price);
	inline bool setProductsPhySize(unsigned int phy_size);
	inline bool setNumOfProducts(unsigned int num_of_prod);
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