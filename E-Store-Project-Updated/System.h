#ifndef __System_h
#define __System_h 

#include <string>
#include <vector>
#include "Seller.h"
#include "Buyer.h"
#include "Buyer_Seller.h"

const int NOT_EXIST = -1;
const int EXIT = -1;
const int EMPTY = 0;
const int MAX_TRIES = 3;

class System
{
private:
	string m_name; //System name

	// Using polymorphistic array: 
	vector<User*> m_user_arr; // Users array

private:
	// Under private cause we don't want anyone to duplicate our system 
	System(const System&s); 
	const System& operator=(const System& s);

public:
	System(const string& name); //c'tor
	~System();// d'tor

public:
	bool operator+=(User* new_user); // Add user to the system

public:
	bool setName(const string& name);

public:
	inline const string& getName()const{ return m_name; }
	inline  vector<User*> getUsersArr()const{ return m_user_arr; }

	// ---------------------------------- maintanance functions ------------------------------------

	const int isUserExist(const string& username)const; // @@@@@@@@@@ should it return ITERATOR?
	
	 // ---------------------------------- MENU functions ------------------------------------

public:
	/*1*/                                       
	//operator += (Add Buyer)
	/*2*/
	//operator += (Add Seller)
	/*3*/
	//operator +=  (Add Buyer_Seller)
	/*4*/
	bool addProductToSeller(Product* prod, const string& seller_username);
	/*5*/
	bool addFeedbackToSeller(const string& buyer_username, const string& seller_username, FeedBack* feedback);
	/*6*/
	bool addProductToBuyersCart(const string& prod_name, const string& buyer_username);
	/*7*/
	bool newOrder(const string& buyer_username);
	/*8*/
	bool payment(const string& buyer_username);
	/*9*/
	void printBuyers()const;
	/*10*/
	void printSellers()const;
	/*11*/
	void printBuyerSellers()const;
	/*12*/
	void printAllSpecificProduct(const string& name_to_find) const;
	/*13*/
	void compareBuyersByCart(const string& username1, const string& username2)const;

	// Print:
	void interactiveMenu();
};

#endif // !__System_h