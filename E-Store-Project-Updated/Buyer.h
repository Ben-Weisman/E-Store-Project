#ifndef __Buyer_h
#define __Buyer_h
#include "User.h"
#include <iostream>

class Order; //forward declaration

class Buyer : virtual public User
{
protected:

	int m_cartPsize;
	int m_number_of_items;
	int m_num_checkout_orders;
	int m_checkout_orders_pSize;

	Product** m_cart;
	Order** m_checkout_orders;

protected:
	// Protected - Cart and checkout orders cannot get changed after initialization
	virtual bool setCart(Product** cart); 
	virtual bool setOrders(Order** other); 

public:
	//			c'tor, copy, d'tor			//
	Buyer(const char* userName, const char* password, const char* fname, const char*
		lname, const Address& address);
	Buyer(const Buyer& b); // copy c'tor
	virtual ~Buyer();

public:

	//			Getters			//
	virtual inline const int getNumberOfItems()const { return m_number_of_items; }
	virtual inline Product** getCart()const { return m_cart; }
	virtual inline Order** getBuyerOrders()const { return m_checkout_orders; }
	virtual inline const int getNumOfOrders()const { return m_num_checkout_orders; }
	virtual double const getTotalCartValue()const;
public:
	//			Arrays maintenance			//
	virtual bool addToCart(Product* item_to_add);
	virtual bool addToCheckout(Order* checkout_order);
	virtual bool removeFromCart(Product* item_to_remove);
	virtual void cartRealloc();
	virtual void checkoutRealloc();

	//			Boolean checks			//
	virtual bool isOrderedFrom(const char* username)const;
	virtual bool isEmptyCheckoutOrders();
	virtual bool isEmptyCart();

public:
	//			Present cart / checkout cart			//
	virtual void showCart()const;
	virtual void showCheckoutOrders()const;

public:

	//			Operators			//
	bool operator>(const Buyer& other)const;
	const Buyer& operator=(const Buyer& other);
	virtual void toOs(ostream& os)const;

	// Declare System class as a friend in order to give it access to the copy c'tor // 
	friend class System;
};

#endif //!__Buyer_h