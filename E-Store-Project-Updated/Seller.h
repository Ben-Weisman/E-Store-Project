#ifndef __Seller_h
#define __Seller_h

#include "FeedBack.h"
#include "Address.h"
#include "Product.h"

class Seller
{
	char* m_username;
	char* m_password;
	char* m_fname;
	char* m_lname;
	int m_feedbacks_phy_size; // Ben please set to 1 by defauld at the c'tor
	int m_num_of_feedbacks; // Ben please set to 0 by defauld at the c'tor
	int m_num_of_listed_items;
	int m_listed_items_pSize;
	Address* m_address;
	FeedBack** m_feedback_arr; 
	Product** m_listed_items;

public:

	// Getters
	inline const char* getFirstName()const;
	inline const char* getLastName()const;
	inline const char* getUsername()const;
	inline const Address* getAddress()const;
	inline const Product **getListedItems()const;
	inline const FeedBack** getFeedbacks()const;

	// Setters
	bool setUserName(const char* username);
	bool setPassword(const char* password);
	bool setFname(const char* fname);
	bool setLname(const char* lname);
	bool setAddress(Address* address);
	bool setListedItems(Product** listed_items);
	bool setFeedBacks(FeedBack** feedbacks);


	// Realloc
	void addToListItems(Product* item_to_add);
	void addToFeedArr(FeedBack* feed_to_add);
	
	void removeFromListItems();
	void removeFromFeedArr();
	
	void reallocateFeedBackArr();
	void reallocateListedItemsArr();
	
	void printSeller();

	~Seller(); // d'tor
	Seller(char* userName = ['\0'], char* password = ['\0'], char* fname = ['\0'], char*
		lname = ['\0'], Address* address = nullptr, Product** listed_items = [nullptr],
		FeedBack** feedbackArray = nullptr);
	Seller(Seller& p); //copy c'tor



public:
	// Realloc:
	void feedbacksRealloc();
	
};

#endif // !__Seller_h

