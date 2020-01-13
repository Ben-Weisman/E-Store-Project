#include "Buyer_Seller.h"
#pragma warning(disable:4996) 

Buyer_Seller::Buyer_Seller(const Buyer& b, const Seller& s) : User(s),
Seller(s), Buyer(b) {} // #### Check why when sending User(s), there's an error. 

const Buyer_Seller& Buyer_Seller::operator=(const Buyer_Seller& other)
{
	User::operator=(other);
	Buyer::operator=(other);
	Seller::operator=(other);
	return *this;
}

void Buyer_Seller::toOs(ostream& os)const
{
	os << "User type: " << typeid(*this).name() + 6;
}


// ----------------------- Buyer's arrays maintenance methods. ----------------------- 

bool Buyer_Seller::addToCart(Product* item_to_add)
{ // Add to buyer's cart using realloc method.
	return Buyer::addToCart(item_to_add);
}

 bool Buyer_Seller::addToCheckout(Order* checkout_order)
{ // Add to Buyer's checkout cart using realloc method.
	 return Buyer::addToCheckout(checkout_order);
}

 bool Buyer_Seller::removeFromCart(Product* item_to_delete)
{ /* Remove a product from buyer's cart by bubbling it to the end of the arr,
	and setting it to nullptr.*/
	 return Buyer::removeFromCart(item_to_delete);
}

void Buyer_Seller::cartRealloc()
{ // Resize cart.
	Buyer::cartRealloc();
}

 void Buyer_Seller::checkoutRealloc()
{ // Resize checkout arr.
	 Buyer::checkoutRealloc();
}


// ----------------------- Printing methods. -----------------------

 void Buyer_Seller::showCart()const
{ // Print buyer's cart.
	 Buyer::showCart();
}

 void Buyer_Seller::showBuyer()const
{ // Print buyer's info.
	 Buyer::showBuyer();
}

 void Buyer_Seller::showCheckoutOrders()const
{ // Show all orders that hasn't been paid yet.
	 Buyer::showCheckoutOrders();
}

// ---------------------------------------------------------------------

 bool Buyer_Seller::isOrderedFrom(const char* username)const
{ // Check if there's an existing order from a given seller, and that it's paid for.
	 return Buyer::isOrderedFrom(username);
}

 bool Buyer_Seller::isEmptyCheckoutOrders()
{ //  Is empty even if there are actual orders in the arr, but they're all paid for. 
	 return Buyer::isEmptyCheckoutOrders();
}

 int const Buyer_Seller::getTotalCartValue()const
{
	 return Buyer::getTotalCartValue();
}

 bool Buyer_Seller::isEmptyCart()
{
	 return Buyer::isEmptyCart();
}

 bool Buyer_Seller::addToListItemsArr(Product* item_to_add)
{ // Add to listed items using realloc method. 
	 return Seller::addToListItemsArr(item_to_add);
}

 bool Buyer_Seller::addToFeedArr(FeedBack* feed_to_add)
{ // Add to feedback arr using realloc method. 
	 return Seller::addToFeedArr(feed_to_add);
}

 bool Buyer_Seller::addToOrdersArr(Order* order_request)
{ // Add to orders arr using realloc method. 
	 return Seller::addToOrdersArr(order_request);
}

 void Buyer_Seller::FeedbackArrRealloc()
{ // Resize feedback arr using realloc logic. 
	 Seller::FeedbackArrRealloc();
}

 void Buyer_Seller::ListedItemsArrRealloc()
{ // Resize listed items arr using realloc logic. 
	 Seller::ListedItemsArrRealloc();
}

 void Buyer_Seller::OrdersArrRealloc()
{ // Resize orders arr using realloc logic. 
	 Seller::OrdersArrRealloc();
}

 void Buyer_Seller::showListedItems()
{
	 Seller::showListedItems();
}

 const Product* Buyer_Seller::findProduct(const char* to_find)const
{ // search for a given product in seller's listed items and return its pointer. 
	 return Seller::findProduct(to_find);
}

// -------------------- Printing methods --------------------

 void Buyer_Seller::showSeller()
{
	 Seller::showSeller();
}


