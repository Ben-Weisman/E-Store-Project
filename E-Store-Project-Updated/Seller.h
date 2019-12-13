#ifndef __Seller_h
#define __Seller_h

#include "FeedBack.h"
#include "Address.h"
#include "Product.h"
#include "Order.h"

class Seller
{
private:
	char* m_username;
	char* m_password;
	char* m_fname;
	char* m_lname;

private:
	int m_feedbacks_phy_size; 
	int m_num_of_feedbacks;
	int m_num_of_listed_items;
	int m_listed_items_pSize;
	int m_num_of_orders;
	int m_orders_pSize;

private:
	Address m_address;
	FeedBack** m_feedback_arr; 
	Product** m_listed_items;
	Order** m_orders;

public:

	// Getters
	inline const char* getFirstName()const;
	inline const char* getLastName()const;
	inline const char* getUsername()const;
	inline const Address getAddress()const;
	inline const Product **getListedItems()const;
	inline const FeedBack** getFeedbacks()const;
	inline const Order** getOrders()const;

public:
	// Setters
	bool setPassword(const char* password);
	bool setFname(const char* fname);
	bool setLname(const char* lname);

public:
	// Realloc
	void addToListItemsArr(Product* item_to_add);
	void addToFeedArr(FeedBack* feed_to_add);
	void addToOrdersArr(Order* order_request);
	
	void FeedbackArrRealloc();
	void ListedItemsArrRealloc();
	void OrdersArrRealloc();
	
	void printSeller();

public:
	~Seller(); // d'tor
	Seller(char* userName, char* password, char* fname, char*
		lname, const Address& address);
	Seller(Seller& p); //copy c'tor	
};

#endif // !__Seller_h

