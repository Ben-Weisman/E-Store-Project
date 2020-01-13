#ifndef __Seller_h
#define __Seller_h
#include "User.h"
#include "FeedBack.h"
#include "Address.h"
#include "Product.h"
#include <iostream>

class Order; //forward declaration

class Seller : virtual public User
{
protected:
	int m_feedbacks_phy_size;
	int m_num_of_feedbacks;
	int m_num_of_listed_items;
	int m_listed_items_pSize;
	int m_num_of_orders;
	int m_orders_pSize;
	
protected:
	FeedBack** m_feedback_arr;
	Product** m_listed_items;
	Order** m_orders;

protected:
	// Setters
	
	virtual bool setFeedBacks(FeedBack** feed);
	virtual bool setOrders(Order** other);
	virtual bool setListItems(Product **listed_items);

public:		
	virtual ~Seller(); // d'tor
	Seller(const char* userName, const char* password, const char* fname, const char*
		lname, const Address& address);
	Seller(const Seller& s); //copy c'tor

	// Getters

	virtual inline  Product **getListedItems()const{ return m_listed_items; }
	virtual inline  FeedBack** getFeedbacks()const{ return m_feedback_arr; }
	virtual inline  Order** getSellerOrders ()const{ return m_orders; }
	virtual inline  const int getNumOfListedItems()const{ return m_num_of_listed_items; }

public:
	//Arrays maintenance
	virtual bool addToListItemsArr(Product* item_to_add);
	virtual bool addToFeedArr(FeedBack* feed_to_add);
	virtual bool addToOrdersArr(Order* order_request);

	// Realloc
	virtual void FeedbackArrRealloc();
	virtual void ListedItemsArrRealloc();
	virtual void OrdersArrRealloc();

	//func
	virtual const Product* findProduct(const char* to_find)const;
	virtual void showSeller();
	virtual void showListedItems();

	//operators
	friend ostream& operator<<(ostream& os, const Seller& seller);
	const Seller& operator=(const Seller& other);
	virtual void toOs(ostream& os)const;

	friend class System;
};

#endif // !__Seller_h

