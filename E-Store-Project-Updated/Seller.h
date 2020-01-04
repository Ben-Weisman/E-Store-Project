#ifndef __Seller_h
#define __Seller_h

#include "FeedBack.h"
#include "Address.h"
#include "Product.h"
#include <iostream>

class Order; //forward declaration

class Seller
{
private:
	char* m_username;
	char* m_password;
	char* m_fname;
	char* m_lname;

private:
	int m_feedbacks_phy_size;
	int m_num_of_feedbacks;
	int m_num_of_listed_items;
	int m_listed_items_pSize;
	int m_num_of_orders;
	int m_orders_pSize;

private:
	Address m_address;
	FeedBack** m_feedback_arr;
	Product** m_listed_items;
	Order** m_orders;

private:
	// Setters
	bool setUsername(char* username);
	bool setFeedBacks(FeedBack** feed);
	bool setOrders(Order** other);
	bool setListItems(Product **listed_items);

public:		


	~Seller(); // d'tor
	Seller(char* userName, char* password, char* fname, char*
		lname, const Address& address);
	Seller(const Seller& s); //copy c'tor

	// Getters
	inline  const char* getFirstName()const{return m_fname; }
	inline  const char* getLastName()const{ return m_lname; }
	inline  const char* getUsername()const{ return m_username; }
	inline  const Address& getAddress()const{ return m_address; }
	inline  Product **getListedItems()const{ return m_listed_items; }
	inline  FeedBack** getFeedbacks()const{ return m_feedback_arr; }
	inline  Order** getOrders()const{ return m_orders; }
	inline  const int getNumOfListedItems()const{ return m_num_of_listed_items; }


public:
	// Setters
	bool setPassword(const char* password);
	bool setFname(const char* fname);
	bool setLname(const char* lname);

public:
	//Arrays maintenance
	bool addToListItemsArr(Product* item_to_add);
	bool addToFeedArr(FeedBack* feed_to_add);
	bool addToOrdersArr(Order* order_request);

	// Realloc
	void FeedbackArrRealloc();
	void ListedItemsArrRealloc();
	void OrdersArrRealloc();

	//func
	const Product* findProduct(const char* to_find)const; // Ben i changed the name to be more intoitive (getProduct sound like getter method - one liner) + added the relevat consts
	void showSeller();

	//operators
	friend ostream& operator<<(ostream& os, const Seller& buyer);
};

#endif // !__Seller_h

