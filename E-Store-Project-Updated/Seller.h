#ifndef __Seller_h
#define __Seller_h
#include "User.h"
#include "FeedBack.h"
#include "Product.h"
#include <iostream>
#include <string>

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
	//			Setters			//
	// No option for re-assigning the following arrays after initialization - thus declared as protected.
	virtual bool setFeedBacks(FeedBack** feed);
	virtual bool setOrders(Order** other);
	virtual bool setListItems(Product **listed_items);
	
public:		
	
	//			c'tor, copy, d'tor			//
	Seller(const string& userName, const string& password, const string& fname, const string&
		lname, const Address& address);
	Seller(const Seller& s); //copy c'tor
	virtual ~Seller(); // d'tor

	//			Getters			//
public:

	virtual inline  Product **getListedItems()const{ return m_listed_items; }
	virtual inline  FeedBack** getFeedbacks()const{ return m_feedback_arr; }
	virtual inline  Order** getSellerOrders ()const{ return m_orders; }
	virtual inline  const int getNumOfListedItems()const{ return m_num_of_listed_items; }

public:

	//			Arrays maintenance			//
	virtual bool addToListItemsArr(Product* item_to_add);
	virtual bool addToFeedArr(FeedBack* feed_to_add);
	virtual bool addToOrdersArr(Order* order_request);

	virtual void FeedbackArrRealloc();
	virtual void ListedItemsArrRealloc();
	virtual void OrdersArrRealloc();

	//			func			//
	virtual const Product* findProduct(const string& to_find)const;
	virtual void showListedItems() const;

	//		Operators			//
	const Seller& operator=(const Seller& other);
	virtual void toOs(ostream& os)const;

	// Declare System class as a friend in order to give it access to the copy c'tor // 
	friend class System;
};

#endif // !__Seller_h

