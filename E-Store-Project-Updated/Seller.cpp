#include "Seller.h"
#include <iostream>
#include <string>
using namespace std;
#pragma warning(disable:4996) 


const char* Seller::getFirstName()const { return m_fname; }
const char* Seller::getLastName()const { return m_lname; }
const char* Seller::getUsername()const { return m_username; }
const Address& Seller::getAddress()const { return m_address; }
Product** Seller::getListedItems()const { return m_listed_items; }
FeedBack** Seller::getFeedbacks()const { return m_feedback_arr; }
Order** Seller::getOrders()const { return m_orders; }
const int Seller::getNumOfListedItems()const { return m_num_of_listed_items; }

const Product* Seller::getProduct(char *to_find)const
{
	for (int i = 0; i < m_num_of_listed_items; i++)
	{
		if (strcmp(this->getListedItems()[i]->getName(), to_find) == 0)
			return this->getListedItems()[i];
	}
	return nullptr;
}

bool Seller::setPassword(const char* password)
{ 
	if (strlen(password) == 0)
		return false;
	delete[]m_password;
	m_password = strdup(password);
	return true;
}

bool Seller::setFname(const char* fname)
{
	if (strlen(fname) == 0)
		return false;
	delete[]m_fname;
	m_fname = strdup(fname);
	return true;
}

bool Seller::setLname(const char* lname)
{
	if (strlen(lname) == 0)
		return false;
	delete[]m_lname;
	m_lname = strdup(lname);
	return true;
}

bool Seller::setUsername(char* username)
{
	if (strlen(username) == 0)
		return false;
	m_username = strdup(username);
	return true;
}

bool Seller::setFeedBacks(FeedBack** feed)
{
	if (!feed)
		return false;
	m_feedback_arr = feed;
	return true;
}

bool Seller::setOrders(Order** other)
{
	if (!other)
		return false;
	m_orders = other;
	return true;
}

bool Seller::setListItems(Product** listed_items)
{
	if (!listed_items)
		return false;
	m_listed_items = listed_items;
	return true;
}

void Seller::addToListItemsArr(Product *item_to_add)
{
	if (m_num_of_listed_items == m_listed_items_pSize)
		ListedItemsArrRealloc();
	m_listed_items[m_num_of_listed_items++] = item_to_add; /*does copy c'tor get called 
														   in such case? */
}

void Seller::addToFeedArr(FeedBack* feed_to_add)
{
	if (m_feedbacks_phy_size == m_num_of_feedbacks)
		FeedbackArrRealloc();
	m_feedback_arr[m_num_of_feedbacks++] = feed_to_add;
}

void Seller::addToOrdersArr(Order* order_request)
{
	if (m_num_of_orders == m_orders_pSize)
		OrdersArrRealloc();
	m_orders[m_num_of_orders++] = order_request;
}

void Seller::FeedbackArrRealloc()
{
	m_feedbacks_phy_size *= 2;
	FeedBack** tmp = new FeedBack*[m_feedbacks_phy_size];

	for (int i = 0; i < m_num_of_feedbacks; i++)
		tmp[i] = m_feedback_arr[i];
	delete m_feedback_arr;
	m_feedback_arr = tmp;
}

void Seller::ListedItemsArrRealloc()
{
	this->m_feedbacks_phy_size *= 2;
	Product** tmp = new Product * [m_feedbacks_phy_size];

	for (int i = 0; i < m_num_of_listed_items; i++)
		tmp[i] = m_listed_items[i];
	delete m_listed_items;

	m_listed_items = tmp;
}

void Seller::OrdersArrRealloc()
{
	this->m_orders_pSize *= 2;
	Order** tmp = new Order * [m_orders_pSize];

	for (int i = 0; i < m_num_of_orders; i++)
		tmp[i] = m_orders[i];
	delete m_orders;

	m_orders = tmp;
}

void Seller::showSeller()
{
	cout << "Name: " << this->getFirstName() << " " << this->getLastName() <<
		endl << "Username: " << this->getUsername() << endl << "Country: " << this->getAddress().getCountry() << endl;
}

Seller::Seller(char* username, char* password, char* fname, char* lname,
	const Address& address) : m_address(address) // c'tor
{
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

	m_orders = new Order * [m_orders_pSize];
	m_orders[m_num_of_orders] = nullptr;

	m_feedback_arr = new FeedBack * [m_feedbacks_phy_size];
	m_feedback_arr[m_num_of_feedbacks] = nullptr;

	m_listed_items = new Product * [m_listed_items_pSize];
	m_listed_items[m_num_of_listed_items] = nullptr;
}


Seller::~Seller() // d'tor
{
	delete[]m_fname;
	delete[]m_lname;
	delete[]m_username;
	delete[]m_password;

	for (int i = 0; i < m_num_of_feedbacks; ++i)
		delete m_feedback_arr[i];

	for (int i = 0; i < m_num_of_listed_items; ++i)
		delete m_listed_items[i];

	for (int i = 0; i < m_num_of_orders; ++i)
		delete m_orders[i];

}

Seller::Seller(const Seller& s):m_address(s.m_address) 
{
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
