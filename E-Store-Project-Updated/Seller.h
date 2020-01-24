#ifndef __Seller_h
#define __Seller_h
#include "User.h"
#include "FeedBack.h"
#include "Product.h"
#include <vector>
#include <iostream>
#include <string>

class Order; //forward declaration

class Seller : virtual public User
{
	
protected:
	vector<FeedBack*> m_feedback_arr;
	vector<Product*> m_listed_items;
	vector<Order*> m_orders;
	
protected:
	//			Setters			//
	// No option for re-assigning the following arrays after initialization - thus declared as protected.
	virtual bool setFeedBacks(vector<FeedBack*> feed);
	virtual bool setOrders(vector<Order*> other);
	virtual bool setListItems(vector<Product*> listed_items);
	
public:		
	
	//			c'tor, copy, d'tor			//
	Seller(const string& userName, const string& password, const string& fname, const string&
		lname, const Address& address);
	//@@@@ C'tor that gets ifStream @@@ 
	Seller(const Seller& s); //copy c'tor
	virtual ~Seller(); // d'tor

	//			Getters			//
public:

	virtual inline  vector<Product*> getListedItems()const{ return m_listed_items; }
	virtual inline  vector<FeedBack*> getFeedbacks()const{ return m_feedback_arr; }
	virtual inline  vector<Order*> getSellerOrders ()const{ return m_orders; }
	virtual inline  const int getNumOfListedItems()const{ return (const int)m_listed_items.size(); }



public:

	//			Arrays maintenance			//
	virtual bool addToListItemsArr(Product* item_to_add);
	virtual bool addToFeedArr(FeedBack* feed_to_add);
	virtual bool addToOrdersArr(Order* order_request);

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

