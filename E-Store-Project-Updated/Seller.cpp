#include "Seller.h"
#include <iostream>
#include <string>
using namespace std;


inline const char* Seller::getFirstName()const { return m_fname; }
inline const char* Seller::getLastName()const { return m_lname; }
inline const char* Seller::getUsername()const { return m_username; }
inline const Address* Seller::getAddress()const { return m_address; }
inline const Product** Seller::getListedItems()const { return m_listed_items; }
inline const FeedBack** Seller::getFeedbacks()const { return m_feedback_arr; }

bool Seller::setUserName(const char* username)
{
	if (strlen(username) == 0)
		return false;
	m_username = strdup(username);
	return true;
}

bool Seller::setPassword(const char* password)
{ 
	if (strlen(password) == 0)
		return false;
	m_password = strdup(password);
	return true;
}

bool Seller::setFname(const char* fname)
{
	if (strlen(fname) == 0)
		return false;
	m_fname = strdup(fname);
	return true;
}

bool Seller::setLname(const char* lname)
{
	if (strlen(lname) == 0)
		return false;
	m_lname = strdup(lname);
	return true;
}

bool Seller::setAddress(Address* address)
{
	if (!address)
		return false;
	m_address = address;
	return true;
}

bool Seller::setListedItems(Product** listed_items)
{
	if (!listed_items)
		return false;
	m_listed_items = listed_items;
	return true;
}
bool Seller::setFeedBacks(FeedBack** feedbacks)
{
	if (!feedbacks)
		return false;
	m_feedback_arr = feedbacks;
	return true;
}

void Seller::addToListItems(Product *item_to_add)
{
	if (m_listed_items == m_listed_items_pSize)
		reallocateListedItemsArr();
	m_listed_items[m_num_of_listed_items++] = item_to_add; /*does copy c'tor get called 
														   in such case? */
}

void Seller::addToFeedArr(FeedBack* feed_to_add)
{
	if (m_feedbacks_phy_size == m_num_of_feedbacks)
		reallocateFeedBackArr();
	m_feedback_arr[m_num_of_feedbacks++] = feed_to_add;
}


void Seller::removeFromListItems()
{
	for (int i = 0; i < m_num_of_listed_items; i++)
	{
		//stopped here
	}
}
void removeFromFeedArr();

void Seller::reallocateFeedBackArr()
{
	m_feedbacks_phy_size *= 2;
	FeedBack** tmp = new FeedBack*[m_feedbacks_phy_size];

	for (int i = 0; i < m_num_of_feedbacks; i++)
		tmp[i] = m_feedback_arr[i];
	delete []m_feedback_arr;
	m_feedback_arr = tmp;
}

void Seller::printSeller()
{
	cout << "Name: " << m_fname << " " << m_lname << endl << "Username: " << m_username << endl
		<< "Password: " << m_password << endl << "Address: " << m_address->printAddress << endl
		<< "Listed Items: " <<endl;

	for (int i = 0; i < m_num_of_listed_items; i++)
		cout << m_listed_items[i]->printProduct << endl;
	cout << "FeedBacks: " << endl;

	for (i = 0; i < m_num_of_feedbacks; i++)
	{
		//cout << m_feedback_arr[i]->printFeedback(); To Implement
	}

}

void Seller::reallocateListedItemsArr()
{
	this->m_feedbacks_phy_size *= 2;
	Product** tmp = new Product * [m_feedbacks_phy_size];
	for (int i = 0; i < m_num_of_listed_items; i++)
		tmp[i] = m_listed_items[i];
	delete[]m_listed_items;

	m_listed_items = tmp;
}

Seller::Seller(char* userName, char* password, char* fname, char* lname,
	Address* address, Product** listed_items,
	FeedBack** feedbackArray)
{
	m_username = strdup(userName);
	m_password = strdup(password);
	m_fname = strdup(fname);
	m_lname = strdup(lname);
	setAddress(address);
	setFeedBacks(feedbackArray);
	setListedItems(listed_items);
	m_num_of_feedbacks = 0;
	m_num_of_listed_items = 0;
	m_feedbacks_phy_size = 1;
	m_listed_items_pSize = 1;
}


Seller::~Seller()
{
	int i;

	delete[]m_fname;
	delete[]m_lname;
	delete[]m_username;
	delete[]m_password;
	delete m_address;

	for (i = 0; i < m_num_of_feedbacks; i++)
		delete m_feedback_arr[i];

	for (i = 0; i < m_num_of_listed_items; i++)
		delete m_listed_items[i];

}





///////////////////////////
void Seller::feedbacksRealloc()
{
		m_feedbacks_phy_size *= 2;

		FeedBack** temp = new FeedBack*[m_feedbacks_phy_size];

		for (int i = 0; i < m_num_of_feedbacks; i++)
		{
			temp[i] = m_feedback_arr[i];
		}
		delete[] m_feedback_arr;

		m_feedback_arr = temp;
}