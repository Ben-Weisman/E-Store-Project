#ifndef __Buyer_h
#define __Buyer_h
#include "Address.h"
#include "Product.h"

class Order;//forword declaration

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

	inline Product** getCart()const;
	inline const int getNumberOfItems()const;
	inline const char* getFirstName()const;
	inline const char* getLastName()const;
	inline const char* getUsername()const;
	inline const Address getAddress()const;
	inline Order** getOrders()const;

	bool setPassword(const char* password);
	bool setFname(const char* fname);
	bool setLname(const char* lname);

	void addToCart(Product* item_to_add);
	void addToCheckout(Order* checkout_order);

	void removeFromCart(Product* item_to_remove);
	
	void showCart()const;
	void showBuyer()const;
	void showCheckoutOrders()const;
	void cartRealloc();
	void checkoutRealloc();

	Buyer(char* userName, char* password, char* fname, char*
		lname, const Address& address);
	Buyer(const Buyer& b); // copy c'tor
	~Buyer();
	
};

#endif //!__Buyer_h