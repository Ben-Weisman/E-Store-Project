#include "Seller.h"
#include <iostream>


using namespace std;
#pragma warning(disable:4996) 

// ----------------- C'tor, Copy C'tor, D'tor -----------------

Seller::Seller(char* username, char* password, char* fname, char* lname,
	const Address& address) : m_address(address) // c'tor
{
	cout << endl << "########################################### IN SELLER C'TOR ###########################################"<< endl;

	setUsername(username);
	setPassword(password);
	setFname(fname);
	setLname(lname);

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
	cout << endl << "########################################### IN SELLER D'TOR ###########################################"<< endl;

	delete[]m_fname;
	delete[]m_lname;
	delete[]m_username;
	delete[]m_password;

	for (int i = 0; i < m_num_of_feedbacks; i++)
		delete m_feedback_arr[i];

	for (int i = 0; i < m_num_of_listed_items; i++)
		delete m_listed_items[i];

	for (int i = 0; i < m_num_of_orders; i++)
		delete m_orders[i];

}

Seller::Seller(const Seller& s) :m_address(s.m_address) // copy c'tor
{
	cout << endl << "########################################### IN SELLER COPY ###########################################"<< endl;

	setUsername(s.m_username);
	setPassword(s.m_password);
	setFname(s.m_fname);
	setLname(s.m_lname);

	m_num_of_feedbacks = s.m_num_of_feedbacks;
	m_feedbacks_phy_size = s.m_num_of_feedbacks;

	m_num_of_listed_items = s.m_num_of_listed_items;
	m_listed_items_pSize = s.m_listed_items_pSize;

	m_num_of_orders = s.m_num_of_orders;
	m_orders_pSize = s.m_orders_pSize;

	setOrders(s.m_orders);
	setFeedBacks(s.m_feedback_arr);
	setListItems(s.m_listed_items);
}


// ----------------- Setters Methods -----------------

bool Seller::setPassword(const char* password)
{ // set password for seller. Validation check - not an empty string.
	if (strlen(password) == 0)
		return false;
	delete[]m_password;
	m_password = strdup(password);
	return true;
}

bool Seller::setFname(const char* fname)
{ // set first name for seller. Validation check - not an empty string.
	if (strlen(fname) == 0)
		return false;
	delete[]m_fname;
	m_fname = strdup(fname);
	return true;
}

bool Seller::setLname(const char* lname)
{ // set last name for seller. Validation check - not an empty string.
	if (strlen(lname) == 0)
		return false;
	delete[]m_lname;
	m_lname = strdup(lname);
	return true;
}

bool Seller::setUsername(char* username) // private - username cannot get changed after initialization 
{  // set username for seller. Validation check - not an empty string.
	if (strlen(username) == 0)
		return false;
	m_username = strdup(username);
	return true;
}

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

	this->m_feedbacks_phy_size *= 2;
	Product** tmp = new Product *[m_feedbacks_phy_size];

	for (int i = 0; i < m_num_of_listed_items; i++)
		tmp[i] = m_listed_items[i];
	delete m_listed_items;

	m_listed_items = tmp;
}

void Seller::OrdersArrRealloc()
{ // Resize orders arr using realloc logic. 
	this->m_orders_pSize *= 2;
	Order** tmp = new Order *[m_orders_pSize];

	for (int i = 0; i < m_num_of_orders; i++)
		tmp[i] = m_orders[i];
	delete m_orders;

	m_orders = tmp;
}

const Product* Seller::findProduct(const char* to_find)const
{ // search for a given product in seller's listed items and return its pointer. 
	for (int i = 0; i < m_num_of_listed_items; i++)
	{
		if (strcmp(this->getListedItems()[i]->getName(), to_find) == 0)
			return this->getListedItems()[i];
	}
	return nullptr;
}

// -------------------- Printing methods --------------------

void Seller::showSeller()
{
	cout << "\tName: " << this->getFirstName() << " " << this->getLastName() <<
		endl << "\tUsername: " << this->getUsername()
		<< endl << "\tCountry: " << this->getAddress().getCountry() << endl;
}


