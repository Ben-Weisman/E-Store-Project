#ifndef __Seller_h
#define __Seller_h

#include "FeedBack.h"
#include "Address.h"
#include "Product.h"

class Order; //forword declaration

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

private:
	// Setters
	bool setUsername(char* username);
	bool setFeedBacks(FeedBack** feed);
	bool setOrders(Order** other);
	bool setListItems(Product **listed_items);

public:

	// Getters
	inline const char* getFirstName()const;
	inline const char* getLastName()const;
	inline const char* getUsername()const;
	inline const Address& getAddress()const;
	inline Product **getListedItems()const;
	inline FeedBack** getFeedbacks()const;
	inline Order** getOrders()const;
	inline const int getNumOfListedItems()const;
	const Product* getProduct(char* to_find)const;

public:
	// Setters
	bool setPassword(const char* password);
	bool setFname(const char* fname);
	bool setLname(const char* lname);

public:
	//Arrays maintenance
	void addToListItemsArr(Product* item_to_add);
	void addToFeedArr(FeedBack* feed_to_add);
	void addToOrdersArr(Order* order_request);
	
	// Realloc
	void FeedbackArrRealloc();
	void ListedItemsArrRealloc();
	void OrdersArrRealloc();
	
	void showSeller();
	

public:
	~Seller(); // d'tor
	Seller(char* userName, char* password, char* fname, char*
		lname, const Address& address);
	Seller(const Seller& s); //copy c'tor	
};

#endif // !__Seller_h

