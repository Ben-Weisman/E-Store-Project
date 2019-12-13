#ifndef __Seller_h
#define __Seller_h

#include "FeedBack.h"
#include "Address.h"
#include "Product.h"
#include "Order"

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
	Address m_address;
	FeedBack** m_feedback_arr; 
	Product** m_listed_items;
	Order **

public:

	// Getters
	inline const char* getFirstName()const;
	inline const char* getLastName()const;
	inline const char* getUsername()const;
	inline const Address getAddress()const;
	inline const Product **getListedItems()const;
	inline const FeedBack** getFeedbacks()const;


	// Setters
	bool setPassword(const char* password);
	bool setFname(const char* fname);
	bool setLname(const char* lname);


	// Realloc
	void addToListItems(Product* item_to_add);
	void addToFeedArr(FeedBack* feed_to_add);
	
	void removeFromListItems();
	void removeFromFeedArr();
	
	void FeedbackArrRealloc();
	void ListedItemsArrRealloc();
	
	void printSeller();

	~Seller(); // d'tor
	Seller(char* userName, char* password, char* fname, char*
		lname, const Address& address);
	Seller(Seller& p); //copy c'tor



public:
	// Realloc:
	void feedbacksRealloc();
	
};

#endif // !__Seller_h

