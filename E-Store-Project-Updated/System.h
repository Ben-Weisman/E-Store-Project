#ifndef __System_h
#define __System_h 

#include "Seller.h"
#include "Buyer.h"
#include "Buyer_Seller.h"

const int MAX_LEN = 21;
const int NOT_EXIST = -1;
const int EXIT = -1;
const int EMPTY = 0;
const int MAX_TRIES = 3;

class System
{
private:
	const char* m_name; //System name

	// Using polymorphistic array: 
	User** m_user_arr; // Users array
	int m_users_phy_size; // Users array physic size
	int m_num_of_users; // Users array logic size

private:
	// Under private cause we don't want anyone to duplicate our system 
	System(const System&s); 
	const System& operator=(const System& s);

public:
	System(const char* name); //c'tor
	~System();// d'tor

public:
	bool operator+=(User* new_user);
	/*bool operator+=(Buyer* new_buyer);
	bool operator+=(Seller* new_seller); 
	bool operator+=(Buyer_Seller* new_buyer_seller);*/

public:
	bool setName(const char* name);

	bool setNumOfUsers(int num_of_users);
	bool setUsersPhySize(int u_physize);


public:
	inline const char* getName()const{ return m_name; }
	
	inline  User** getUsersArr()const{ return m_user_arr; }
	inline  int getUsersPhySize()const{ return m_users_phy_size; }
	inline  int getNumOfUsers()const{ return m_num_of_users; }


	// ---------------------------------- maintanance functions ------------------------------------

	const int isUserExist(const char* username)const;
	void usersRealloc();
	

	 // ---------------------------------- MENU functions ------------------------------------

public:
	/*1*/                                       
	//operator += (Add Buyer)
	/*2*/
	//operator += (Add Seller)
	/*3*/
	//operator +=  (Add Buyer_Seller)
	/*4*/
	bool addProductToSeller(Product* prod, const char* seller_username);
	/*5*/
	bool addFeedbackToSeller(const char* buyer_username, const char* seller_username, FeedBack* feedback);
	/*6*/
	bool addProductToBuyersCart(const char* prod_name, const char* buyer_username);
	/*7*/
	bool newOrder(const char* buyer_username);
	/*8*/
	bool payment(const char* buyer_username);
	/*9*/
	void printBuyers()const;
	/*10*/
	void printSellers()const;
	/*11*/
	void printBuyerSellers()const;
	/*12*/
	void printAllSpecificProduct(const char* name_to_find) const;
	/*13*/
	void compareBuyersByCart(const char* username1, const char* username2)const;

	// Print:
	void interactiveMenu();
};

#endif // !__System_h