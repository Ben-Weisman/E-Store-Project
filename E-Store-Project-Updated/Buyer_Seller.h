#ifndef __Buyer_Seller_h
#define __Buyer_Seller_h
#include <iostream>
#include "Buyer.h"
#include "Seller.h"

using namespace std;

class Buyer_Seller : public Seller, public Buyer
{
public:
	// No need for overriding the default copy c'tor & d'tor - No allocated data members in this class.
	Buyer_Seller(const Buyer& b, const Seller& s);   // c'tor

public:

	// ---------------------------------------------------------------------------- //
	// ------------------------------ Seller Methods ------------------------------ // 
	// ---------------------------------------------------------------------------- //

	//			Getters			//
	virtual inline  Product** getListedItems()const { return m_listed_items; }
	virtual inline  FeedBack** getFeedbacks()const { return m_feedback_arr; }
	virtual inline  Order** getSellerOrders()const { return m_orders; }
	virtual inline  const int getNumOfListedItems()const { return m_num_of_listed_items; }

public:
	//			Arrays maintenance			//
	virtual bool addToListItemsArr(Product* item_to_add);
	virtual bool addToFeedArr(FeedBack* feed_to_add);
	virtual bool addToOrdersArr(Order* order_request);

	//			Realloc			//
	virtual void FeedbackArrRealloc();
	virtual void ListedItemsArrRealloc();
	virtual void OrdersArrRealloc();

	//			func			//
	virtual const Product* findProduct(const char* to_find)const;
	virtual void showListedItems() const;

	
	// ---------------------------------------------------------------------------- //
	// ------------------------------ Buyer Methods ------------------------------ // 
	// ---------------------------------------------------------------------------- //

public:
	//			Getters			//
	virtual inline const int getNumberOfItems()const { return m_number_of_items; }
	virtual inline Product** getCart()const { return m_cart; }
	virtual inline Order** getBuyerOrders()const { return m_checkout_orders; }
	virtual inline const int getNumOfOrders()const { return m_num_checkout_orders; }
	virtual double getTotalCartValue()const;
public:

	//			Arrays maintenance			//
	virtual bool addToCart(Product* item_to_add);
	virtual bool addToCheckout(Order* checkout_order);
	virtual bool removeFromCart(Product* item_to_remove);
	virtual void cartRealloc();
	virtual void checkoutRealloc();

	//			Boolean checks			//
	virtual bool isOrderedFrom(const char* username)const;
	virtual bool isEmptyCheckoutOrders();
	virtual bool isEmptyCart();

public:
	//			Print carts methods			//
	virtual void showCart()const;
	virtual void showCheckoutOrders()const;

public:
	//			Operators			//
	const Buyer_Seller& operator=(const Buyer_Seller& other); 
	virtual void toOs(ostream& os)const;
};

#endif // !__Buyer_Seller_h