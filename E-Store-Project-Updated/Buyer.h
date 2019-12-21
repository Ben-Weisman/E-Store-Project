#ifndef __Buyer_h
#define __Buyer_h
#include "Address.h"
#include "Product.h"

class Order; //forward declaration

class Buyer
{
private:
	char* m_username;
	char* m_password;
	char* m_fname;
	char* m_lname;

	int m_cartPsize;
	int m_number_of_items;
	int m_num_checkout_orders;
	int m_checkout_orders_pSize;

	Address m_address;
	Product** m_cart;
	Order** m_checkout_orders;

private:
	bool setUsername(char* username);
	bool setCart(Product** cart);

public:

	Buyer(char* userName, char* password, char* fname, char*
		lname, const Address& address);
	Buyer(const Buyer& b); // copy c'tor
	~Buyer();

public:

	inline const int getNumberOfItems()const { return m_number_of_items; }
	inline const char* getFirstName()const { return m_fname; }
	inline const char* getLastName()const { return m_lname; }
	inline const char* getUsername()const { return m_username; }
	inline Product** getCart()const { return m_cart; }
	inline const Address& getAddress()const { return m_address; }
	inline Order** getOrders()const { return m_checkout_orders; }
	inline const int getNumOfOrders()const { return m_num_checkout_orders; }

public:

	bool setPassword(const char* password);
	bool setFname(const char* fname);
	bool setLname(const char* lname);
	bool setOrder(Order** order);

public:

	bool addToCart(Product* item_to_add);
	bool addToCheckout(Order* checkout_order);
	bool removeFromCart(Product* item_to_remove);
	void cartRealloc();
	void checkoutRealloc();
	bool isOrderedFrom(const char* username)const;
	bool isEmptyCheckoutOrders();
	bool isEmptyCart();

public:

	void showCart()const;
	void showBuyer()const;
	void showCheckoutOrders()const;

};

#endif //!__Buyer_h