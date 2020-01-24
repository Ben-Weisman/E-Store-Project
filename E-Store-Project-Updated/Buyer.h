#ifndef __Buyer_h
#define __Buyer_h
#include "User.h"
#include "Array.h"
#include <string>
#include <vector>
#include <iostream>

class Order; //forward declaration

class Buyer : virtual public User
{
protected:

	Array<Product> m_cart;
	vector<Order*> m_checkout_orders;
	
protected:
	// Protected - Cart and checkout orders cannot get re-initialazied changed after first initialization
	virtual bool setCart(Product** cart); // Array
	virtual bool setOrders(vector<Order*> other); // Vector

public:
	//			c'tor, copy, d'tor			//
	Buyer(const string& userName, const string& password, const string& fname, const string&
		lname, const Address& address);
	//@@@@ C'tor that gets ifStream @@@ 
	Buyer(const Buyer& b); // copy c'tor
	virtual ~Buyer();

public:

	//			Getters			//
	virtual inline Product** getCart()const { return m_cart.getArray(); }
	virtual inline vector<Order*> getBuyerOrders()const { return m_checkout_orders; }
	virtual double getTotalCartValue()const;
	virtual inline const int getNumOfOrders()const { return (const int)m_checkout_orders.size(); }
public:
	//			Arrays maintenance			//
	virtual bool addToCart(Product* item_to_add);
	virtual bool addToCheckout(Order* checkout_order);
	virtual bool removeFromCart(Product* item_to_remove);

	//			Boolean checks			//
	virtual bool isOrderedFrom(const string& username)const;
	virtual bool isEmptyCheckoutOrders();
	virtual bool isEmptyCart();

public:
	//			Present cart (type Product) / checkout cart	(Type Order)		//
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