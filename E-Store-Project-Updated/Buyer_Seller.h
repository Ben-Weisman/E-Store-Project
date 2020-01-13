#ifndef __Buyer_Seller_h
#define __Buyer_Seller_h
#include <iostream>
#include "Buyer.h"
#include "Seller.h"
//#include "User.h"
#include "FeedBack.h"

using namespace std;

class Buyer_Seller : public Seller, public Buyer
{
public:
	Buyer_Seller(const Buyer& b, const Seller& s); //##Nir: maybe we should change, according to System.cpp line 490  

public:

	// ---------------------------------------------------------------------------- //
	// ------------------------------ Seller Methods ------------------------------ // 
	// ---------------------------------------------------------------------------- //

	// Getters

	virtual inline  Product** getListedItems()const { return m_listed_items; }
	virtual inline  FeedBack** getFeedbacks()const { return m_feedback_arr; }
	virtual inline  Order** getSellerOrders()const { return m_orders; }
	virtual inline  const int getNumOfListedItems()const { return m_num_of_listed_items; }

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

	
	// ---------------------------------------------------------------------------- //
	// ------------------------------ Buyer Methods ------------------------------ // 
	// ---------------------------------------------------------------------------- //

public:

	virtual inline const int getNumberOfItems()const { return m_number_of_items; }
	virtual inline Product** getCart()const { return m_cart; }
	virtual inline Order** getBuyerOrders()const { return m_checkout_orders; }
	virtual inline const int getNumOfOrders()const { return m_num_checkout_orders; }
	virtual int const getTotalCartValue()const;
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
	const Buyer_Seller& operator=(const Buyer_Seller& other); // modify to Buyer_Seller
	virtual void toOs(ostream& os)const;// modify to Buyer_Seller
};

#endif // !__Buyer_Seller_h