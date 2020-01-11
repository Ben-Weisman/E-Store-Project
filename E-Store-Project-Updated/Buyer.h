#ifndef __Buyer_h
#define __Buyer_h
#include "Address.h"
#include "Product.h"
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
	virtual bool setCart(Product** cart);

public:

	Buyer(char* userName, char* password, char* fname, char*
		lname, const Address& address);
	Buyer(const Buyer& b); // copy c'tor
	virtual ~Buyer();

public:

	virtual inline const int getNumberOfItems()const { return m_number_of_items; }
	virtual inline Product** getCart()const { return m_cart; }
	virtual inline Order** getOrders()const { return m_checkout_orders; }
	virtual inline const int getNumOfOrders()const { return m_num_checkout_orders; }
	virtual int const getTotalCartValue()const;

public:

	virtual bool setOrder(Order** order);

public:

	virtual bool addToCart(Product* item_to_add);
	virtual bool addToCheckout(Order* checkout_order);
	virtual bool removeFromCart(Product* item_to_remove);
	virtual void cartRealloc();
	virtual void checkoutRealloc();
	virtual bool isOrderedFrom(const char* username)const;
	virtual bool isEmptyCheckoutOrders();
	virtual bool isEmptyCart();

public:

	virtual void showCart()const;
	virtual void showBuyer()const; // NO delete
	virtual void showCheckoutOrders()const;

public:
	friend ostream& operator<<(ostream& os, const Buyer& buyer);
	bool operator>(const Buyer& other)const;
	const Buyer& operator=(const Buyer& other);

	virtual void toOs(ostream& os)const {};

};

#endif //!__Buyer_h