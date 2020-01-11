#include "Buyer_Seller.h"

Buyer_Seller::Buyer_Seller(const Buyer& b, const Seller& s) : User(b),
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
	os << typeid(*this).name() + 6;
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
	m_checkout_orders_pSize *= 2;

	Order** tmp = new Order * [m_checkout_orders_pSize];

	for (int i = 0; i < m_num_checkout_orders; i++)
		tmp[i] = m_checkout_orders[i];
	delete m_checkout_orders;

	m_checkout_orders = tmp;
}


// ----------------------- Printing methods. -----------------------

 void Buyer_Seller::showCart()const
{ // Print buyer's cart.

	if (m_number_of_items == 0)
		cout << endl << "No products to show, your cart is currently empty." << endl <<
		"Please search for products to buy or go to your checkout cart to continue with your order" << endl;
	else {
		cout << "All products are in #/Name/Price/Seller format" << endl;

		for (int i = 0; i < m_number_of_items; i++)
			cout << i + 1 << ") " << m_cart[i]->getName() << "\t" << m_cart[i]->getPrice() <<
			"$\t" << m_cart[i]->getSellerUsername() << endl;
	}
}

 void Buyer_Seller::showBuyer()const
{ // Print buyer's info.
	cout << "\tFull Name: " << m_fname << " " << m_lname << endl;
	cout << "\tUsername: " << m_username << endl;
	cout << "\tFrom: " << m_address.getCountry() << endl;
}

 void Buyer_Seller::showCheckoutOrders()const
{ // Show all orders that hasn't been paid yet.
	for (int i = 0; i < m_num_checkout_orders; i++)
	{
		if (!this->m_checkout_orders[i]->getPaid())
		{
			cout << "\n\t Order #" << i + 1 << endl;
			this->m_checkout_orders[i]->showOrder();
		}
	}
}

// ---------------------------------------------------------------------

 bool Buyer_Seller::isOrderedFrom(const char* username)const
{ // Check if there's an existing order from a given seller, and that it's paid for.
	for (int i = 0; i < this->m_num_checkout_orders; i++)
	{
		for (int j = 0; j < m_checkout_orders[i]->getNumOfProducts(); j++)
		{
			if (strcmp(this->m_checkout_orders[i]->getProductsArr()[j]->getSellerUsername(), username) == 0)
			{
				if (this->m_checkout_orders[i]->getPaid())
					return true;
			}
		}
	}
	return false;
}

 bool Buyer_Seller::isEmptyCheckoutOrders()
{ //  Is empty even if there are actual orders in the arr, but they're all paid for. 
	for (int i = 0; i < this->getNumOfOrders(); i++)
	{
		if (!this->getBuyerOrders()[i]->getPaid())
			return false;
	}
	return true;
}

 int const Buyer_Seller::getTotalCartValue()const
{
	int res = 0;

	for (int i = 0; i < this->getNumberOfItems(); i++)
		res += this->m_cart[i]->getPrice();
	for (int i = 0; i < this->getNumOfOrders(); i++)
	{
		if (!this->m_checkout_orders[i]->getPaid())
		{
			for (int j = 0; j < this->m_checkout_orders[i]->getNumOfProducts(); j++)
				res += this->m_checkout_orders[i]->getProductsArr()[j]->getPrice();
		}
	}
	return res;
}

 bool Buyer_Seller::isEmptyCart()
{
	if (this->m_number_of_items == 0)
		return true;
	return false;
}

 bool Buyer_Seller::addToListItemsArr(Product* item_to_add)
{ // Add to listed items using realloc method. 
	if (!item_to_add)
		return false;
	if (m_num_of_listed_items == m_listed_items_pSize)
		ListedItemsArrRealloc();
	m_listed_items[m_num_of_listed_items++] = item_to_add;
	return true;
}

 bool Buyer_Seller::addToFeedArr(FeedBack* feed_to_add)
{ // Add to feedback arr using realloc method. 
	if (!feed_to_add)
		return false;
	if (m_feedbacks_phy_size == m_num_of_feedbacks)
		FeedbackArrRealloc();
	m_feedback_arr[m_num_of_feedbacks++] = feed_to_add;
	return true;
}

 bool Buyer_Seller::addToOrdersArr(Order* order_request)
{ // Add to orders arr using realloc method. 
	if (!order_request)
		return false;
	if (m_num_of_orders == m_orders_pSize)
		OrdersArrRealloc();
	m_orders[m_num_of_orders++] = order_request;
	return true;
}

 void Buyer_Seller::FeedbackArrRealloc()
{ // Resize feedback arr using realloc logic. 

	m_feedbacks_phy_size *= 2;
	FeedBack** tmp = new FeedBack * [m_feedbacks_phy_size];

	for (int i = 0; i < m_num_of_feedbacks; i++)
		tmp[i] = m_feedback_arr[i];
	delete m_feedback_arr;
	m_feedback_arr = tmp;
}

 void Buyer_Seller::ListedItemsArrRealloc()
{ // Resize listed items arr using realloc logic. 

	m_feedbacks_phy_size *= 2;
	Product** tmp = new Product * [m_feedbacks_phy_size];

	for (int i = 0; i < m_num_of_listed_items; i++)
		tmp[i] = m_listed_items[i];
	delete m_listed_items;

	m_listed_items = tmp;
}

 void Buyer_Seller::OrdersArrRealloc()
{ // Resize orders arr using realloc logic. 
	m_orders_pSize *= 2;
	Order** tmp = new Order * [m_orders_pSize];

	for (int i = 0; i < m_num_of_orders; i++)
		tmp[i] = m_orders[i];
	delete m_orders;

	m_orders = tmp;
}

 void Buyer_Seller::showListedItems()
{
	for (int i = 0; i < m_num_of_listed_items; i++)
		cout << m_listed_items[i];
}

 const Product* Buyer_Seller::findProduct(const char* to_find)const
{ // search for a given product in seller's listed items and return its pointer. 
	for (int i = 0; i < m_num_of_listed_items; i++)
	{
		if (strcmp(m_listed_items[i]->getName(), to_find) == 0)
			return this->m_listed_items[i];
	}
	return nullptr;
}

// -------------------- Printing methods --------------------

 void Buyer_Seller::showSeller()
{
	cout << "\tName: " << m_fname << " " << m_lname <<
		endl << "\tUsername: " << m_username
		<< endl << "\tCountry: " << m_address.getCountry() << endl;
}

