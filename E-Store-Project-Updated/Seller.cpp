#include "Seller.h"
#include "Utils.h"
#include <iostream>


using namespace std;
#pragma warning(disable:4996) 

// ----------------- C'tor, Copy C'tor, D'tor -----------------

Seller::Seller(const char* username, const char* password, const char* fname, const char* lname,
	const Address& address) :User(username, password, fname, lname, address) // c'tor
{
	m_num_of_feedbacks = 0;
	m_num_of_listed_items = 0;
	m_feedbacks_phy_size = 1;
	m_listed_items_pSize = 1;
	m_num_of_orders = 0;
	m_orders_pSize = 1;

	m_orders = new Order *[m_orders_pSize];
	m_orders[m_num_of_orders] = nullptr;

	m_feedback_arr = new FeedBack *[m_feedbacks_phy_size];
	m_feedback_arr[m_num_of_feedbacks] = nullptr;

	m_listed_items = new Product *[m_listed_items_pSize];
	m_listed_items[m_num_of_listed_items] = nullptr;
}


Seller::~Seller() // d'tor
{
	for (int i = 0; i < m_num_of_feedbacks; i++)
		delete m_feedback_arr[i];

	for (int i = 0; i < m_num_of_listed_items; i++)
		delete m_listed_items[i];

	for (int i = 0; i < m_num_of_orders; i++)
		delete m_orders[i];
}

Seller::Seller(const Seller& s) :User(s) // copy c'tor
{
	*this = s;
}


// ----------------- Setters Methods -----------------

bool Seller::setFeedBacks(FeedBack** feed) // private - Feedbacks cannot get changed after initialization
{  // set feedbacks for seller. Validation check - pointer exists.

	if (!feed)
		return false;
	m_feedback_arr = feed;
	return true;
}

bool Seller::setOrders(Order** other) // private - Orders cannot get changed after initialization
{  // set orders for seller. Validation check - pointer exists.
	if (!other)
		return false;
	m_orders = other;
	return true;
}

bool Seller::setListItems(Product** listed_items) // private - listed items cannot get changed after initialization
{  // set listed items for seller. Validation check - pointer exists.
	if (!listed_items)
		return false;
	m_listed_items = listed_items;
	return true;
}


// ----------------- Seller's maintenance methods -----------------

bool Seller::addToListItemsArr(Product *item_to_add)
{ // Add to listed items using realloc method. 
	if (!item_to_add)
		return false;
	if (m_num_of_listed_items == m_listed_items_pSize)
		ListedItemsArrRealloc();
	m_listed_items[m_num_of_listed_items++] = item_to_add;
	return true;
}

bool Seller::addToFeedArr(FeedBack* feed_to_add)
{ // Add to feedback arr using realloc method. 
	if (!feed_to_add)
		return false;
	if (m_feedbacks_phy_size == m_num_of_feedbacks)
		FeedbackArrRealloc();
	m_feedback_arr[m_num_of_feedbacks++] = feed_to_add;
	return true;
}

bool Seller::addToOrdersArr(Order* order_request)
{ // Add to orders arr using realloc method. 
	if (!order_request)
		return false;
	if (m_num_of_orders == m_orders_pSize)
		OrdersArrRealloc();
	m_orders[m_num_of_orders++] = order_request;
	return true;
}

void Seller::FeedbackArrRealloc()
{ // Resize feedback arr using realloc logic. 

	m_feedbacks_phy_size *= 2;
	FeedBack** tmp = new FeedBack*[m_feedbacks_phy_size];

	for (int i = 0; i < m_num_of_feedbacks; i++)
		tmp[i] = m_feedback_arr[i];
	delete m_feedback_arr;
	m_feedback_arr = tmp;
}

void Seller::ListedItemsArrRealloc()
{ // Resize listed items arr using realloc logic. 

	m_feedbacks_phy_size *= 2;
	Product** tmp = new Product *[m_feedbacks_phy_size];

	for (int i = 0; i < m_num_of_listed_items; i++)
		tmp[i] = m_listed_items[i];
	delete m_listed_items;

	m_listed_items = tmp;
}

void Seller::OrdersArrRealloc()
{ // Resize orders arr using realloc logic. 
	m_orders_pSize *= 2;
	Order** tmp = new Order *[m_orders_pSize];

	for (int i = 0; i < m_num_of_orders; i++)
		tmp[i] = m_orders[i];
	delete m_orders;

	m_orders = tmp;
}

void Seller::showListedItems() const
{
	for (int i = 0; i < m_num_of_listed_items; i++)
		cout << m_listed_items[i];
}

const Product* Seller::findProduct(const char* to_find)const
{ // search for a given product in seller's listed items and return its pointer. 
	for (int i = 0; i < m_num_of_listed_items; i++)
	{
		if (strcmp(m_listed_items[i]->getName(), to_find) == 0)
			return this->m_listed_items[i];
	}
	return nullptr;
}

// -------------------- Printing methods --------------------

ostream& operator<<(ostream& os, Seller& seller) 
{ 
	os << "Full Name: " << (User&)seller;
	return os;
}
const Seller& Seller::operator=(const Seller& other)
{
	if (this != &other)
	{
		User::operator=(other);

		m_feedbacks_phy_size = other.m_feedbacks_phy_size;
		m_num_of_feedbacks = other.m_num_of_feedbacks;
		m_num_of_listed_items = other.m_num_of_listed_items;
		m_listed_items_pSize = other.m_listed_items_pSize;
		m_num_of_orders = other.m_num_of_orders;
		m_orders_pSize = other.m_orders_pSize;

		m_listed_items = new Product * [m_listed_items_pSize];
		m_orders = new Order * [m_orders_pSize];
		m_feedback_arr = new FeedBack * [m_feedbacks_phy_size];

		for (int i = 0; i < m_num_of_feedbacks; i++)
			*(m_feedback_arr+i) = *(other.m_feedback_arr+i);

		for (int i = 0; i < m_num_of_listed_items; i++)
			*(m_listed_items+i) = *(other.m_listed_items+i);

		for (int i = 0; i < m_num_of_orders; i++)
			*(m_orders+i) = *(other.m_orders+i);
	}
	return *this;
}
void Seller::toOs(ostream& os)const
{
	os << "\n\tUser type: " <<typeid(*this).name() + 6;
}


