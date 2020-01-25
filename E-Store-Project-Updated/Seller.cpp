#include "Seller.h"
#include "Utils.h"
#include <iostream>
using namespace std;




// ----------------- C'tor, Copy C'tor, D'tor -----------------

Seller::Seller(const string& username, const string& password, const string& fname, const string& lname,
	const Address& address) :User(username, password, fname, lname, address) // c'tor
{

}
Seller::Seller(ifstream& in_file):User(in_file)
{
}

Seller::~Seller() // d'tor
{
	for (auto feed_ptr : m_feedback_arr)
		delete feed_ptr;

	for (auto product_ptr : m_listed_items)
		delete product_ptr;

	for (auto order_ptr : m_orders)
		delete order_ptr;

	cout << "/n##Seller Dtor with: " << this->m_username; "####/n";//@@@
}

Seller::Seller(const Seller& other) :User(other) // copy c'tor
{ // Don't call the assignment operator because it calls the assignment of User, and we want to keep
	// the call in the init list. - After consulting with the lecturer.
	
	m_feedback_arr.reserve(other.getFeedbacks().capacity());
	m_listed_items.reserve(other.getListedItems().capacity());
	m_orders.reserve(other.getSellerOrders().capacity());

	for (auto feed_ptr : other.m_feedback_arr)
		m_feedback_arr.push_back(new FeedBack(*feed_ptr));

	for (auto product_ptr : other.m_listed_items)
		m_listed_items.push_back(new Product(*product_ptr));

	for (auto order_ptr : other.m_orders)
		m_orders.push_back(new Order(*order_ptr));
}


// ----------------- Setters Methods -----------------

bool Seller::setFeedBacks(vector<FeedBack*> feed_arr) // private - Feedbacks cannot get changed after initialization
{  // set feedbacks for seller. Validation check - is empty vector container.

	if (feed_arr.empty())
		return false;
	m_feedback_arr = feed_arr;
	return true;
}

bool Seller::setOrders(vector<Order*> other) // private - Orders cannot get changed after initialization
{  // set orders for seller. Validation check - is empty vector container.
	if (other.empty())
		return false;
	m_orders = other;
	return true;
}

bool Seller::setListItems(vector<Product*> listed_items) // private - listed items cannot get changed after initialization
{  // set listed items for seller. Validation check - is empty vector container.
	if (listed_items.empty())
		return false;
	m_listed_items = listed_items;
	return true;
}


//		Arrays maintenance methods			//

bool Seller::addToListItemsArr(Product *item_to_add)
{ // Add to listed items using realloc method. 
	if (!item_to_add)
		return false;

	if (m_listed_items.size() == m_listed_items.capacity())
		m_listed_items.reserve(m_listed_items.capacity() * 2);
	m_listed_items.push_back(item_to_add);
	return true;
}

bool Seller::addToFeedArr(FeedBack* feed_to_add)
{ // Add to feedback arr using realloc method. 
	if (!feed_to_add)
		return false;

	if (m_feedback_arr.size() == m_feedback_arr.capacity())
		m_feedback_arr.reserve(m_feedback_arr.capacity() * 2);
	m_feedback_arr.push_back(feed_to_add);
	return true;
}

bool Seller::addToOrdersArr(Order* order_request)
{ // Add to orders arr using realloc method. 
	if (!order_request)
		return false;

	if (m_orders.size() == m_orders.capacity())
		m_orders.reserve(m_orders.capacity() * 2);
	m_orders.push_back(order_request);
	return true;
}

// ----------------------------------------------------------------- //

const Product* Seller::findProduct(const string& to_find)const
{ // search for a given product in seller's listed items and return its pointer. 

	for (auto product_ptr : m_listed_items)
	{
		if (product_ptr->getName() == to_find)
			return product_ptr;
	}
	return nullptr;
}

//			Print method			//

ostream& operator<<(ostream& os, Seller& seller) 
{ 
	os << "Full Name: " << (User&)seller;
	return os;
}

void Seller::showListedItems() const
{
	for (auto product_ptr : m_listed_items)
		cout << product_ptr;

}

//			Operators			//

const Seller& Seller::operator=(const Seller& other)
{
	if (this != &other)
	{
		User::operator=(other);

		m_feedback_arr.reserve(other.getFeedbacks().capacity());
		m_listed_items.reserve(other.getListedItems().capacity());
		m_orders.reserve(other.getSellerOrders().capacity());

		for (auto feed_ptr : other.m_feedback_arr)
			m_feedback_arr.push_back(new FeedBack(*feed_ptr));
		for (auto product_ptr : other.m_listed_items)
			m_listed_items.push_back(new Product(*product_ptr));
		for (auto order_ptr : other.m_orders)
			m_orders.push_back(new Order(*order_ptr));

	}
	return *this;
}
void Seller::toOs(ostream& os)const
{
	os << "\n\tUser type: " <<typeid(*this).name() + 6;
}


