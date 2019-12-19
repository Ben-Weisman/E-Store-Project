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

	 Product** getCart()const;
	 const int getNumberOfItems()const;
	 const char* getFirstName()const;
	 const char* getLastName()const;
	 const char* getUsername()const;
	 const Address& getAddress()const;
	 Order** getOrders()const;
	 const int getNumOfItems()const;
	 const int getNumOfOrders()const;

public:

	bool setPassword(const char* password);
	bool setFname(const char* fname);
	bool setLname(const char* lname);
	bool setOrder(Order** order);

	void addToCart(Product* item_to_add);
	void addToCheckout(Order* checkout_order);

	void removeFromCart(Product* item_to_remove);

	void cartRealloc();
	void checkoutRealloc();

	void showCart()const;
	void showBuyer()const;
	void showCheckoutOrders()const;


	bool isOrderedFrom(const char* username)const; //Nir:
	//added 2 consts: 1) because the func do not change the object
	//added 2 consts: 1) because we don't want anyoneto change the username that we searching for


};

#endif //!__Buyer_h