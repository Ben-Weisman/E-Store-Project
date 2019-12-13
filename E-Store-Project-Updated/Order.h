#ifndef __Order_h
#define __Order_h
#include "Product.h"
#include "Buyer.h"
#include "Seller.h" 

class Order
{
	Product** m_checkout_arr;
	unsigned int m_products_phy_size;
	unsigned int m_num_of_products;
	unsigned int m_total_price;
	Seller * const m_seller; 
	Buyer * const m_buyer; 
	
public:
	Order(unsigned int total_price); 
	~Order();

public:
	inline bool setTotalPrice(unsigned int total_price);
	inline bool setProductsPhySize(unsigned int phy_size);
	inline bool setNunOfProducts(unsigned int num_of_prod);

	// Do we need setters to buyer&seller ?

public:
	inline unsigned int getTotalPrice()const;
	inline unsigned int getProductsPhySize()const;
	inline unsigned int getNunOfProducts()const;
	inline const Seller& getSeller()const;
	inline const Buyer& getBuyer()const;
	Product** getProductsArr()const;
	
public:
	void deleteFromCart();
};

#endif //!__Order_h