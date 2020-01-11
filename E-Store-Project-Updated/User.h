#ifndef __User_h
#define __User_h
#include <iostream>
#include "Address.h"
using namespace std;

class User
{
protected:

	char* m_username;
	char* m_password;
	char* m_fname;
	char* m_lname;

	Address m_address;

	User(const char* userName, const char* password, const char* fname, const char*
		lname, const Address& address);
	User(const User& u); //copy c'tor

protected:
	bool setUsername(const char* username);
	bool setPassword(const char* password);
	bool setFname(const char* fname);
	bool setLname(const char* lname);
	bool setAddress(const Address& address); // ####### Need to implement

public:
	virtual ~User(); // d'tor

	inline  const char* getFirstName()const { return m_fname; }
	inline  const char* getLastName()const { return m_lname; }
	inline  const char* getUsername()const { return m_username; }
	inline  const Address& getAddress()const { return m_address; }

public:
	const User& operator=(const User& other);
	friend ostream& operator<<(ostream& os, const User& buyer);
	virtual void toOs(ostream& os)const {};

public:
	//-------------------- Buyer Methods --------------------//
	// Defining all Buyer's methods as pure virtual in User class.
	virtual inline const int getNumberOfItems()const = 0;
	virtual inline Product** getCart()const = 0;
	virtual inline Order** getOrders()const = 0;
	virtual inline const int getNumOfOrders()const = 0;
	virtual int const getTotalCartValue()const = 0;
	
	virtual bool setOrder(Order** order) = 0;

	virtual bool addToCart(Product* item_to_add) = 0;
	virtual bool addToCheckout(Order* checkout_order) = 0;
	virtual bool removeFromCart(Product* item_to_remove) = 0;
	virtual void cartRealloc() = 0;
	virtual void checkoutRealloc() = 0;
	virtual bool isOrderedFrom(const char* username)const = 0;
	virtual bool isEmptyCheckoutOrders() = 0;
	virtual bool isEmptyCart() = 0;

public:

	virtual void showCart()const = 0;
	virtual void showBuyer()const = 0; // NO delete?
	virtual void showCheckoutOrders()const = 0;

public:
	//-------------------- Seller Methods --------------------//
	// Defining all Seller's methods as pure virtual in User class.
	virtual inline  Product** getListedItems()const = 0;
	virtual inline  FeedBack** getFeedbacks()const = 0;
	virtual inline  Order** getOrders()const = 0;
	virtual inline  const int getNumOfListedItems()const = 0;

public:
			//Arrays maintenance
	virtual bool addToListItemsArr(Product* item_to_add) = 0;
	virtual bool addToFeedArr(FeedBack* feed_to_add) = 0;
	virtual bool addToOrdersArr(Order* order_request) = 0;

			// Realloc
	virtual void FeedbackArrRealloc() = 0;
	virtual void ListedItemsArrRealloc() = 0;
	virtual void OrdersArrRealloc() = 0;

			//func
	virtual const Product* findProduct(const char* to_find)const = 0;
	virtual void showSeller() = 0;
	virtual void showListedItems() = 0;

protected:
	virtual bool setFeedBacks(FeedBack** feed) = 0;
	virtual bool setOrders(Order** other) = 0;
	virtual bool setListItems(Product** listed_items) = 0;
};



#endif // !__User_h