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
	bool operator+=(Buyer* new_buyer); // use POLY
	bool operator+=(Seller* new_seller); // use POLY 
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
	/*bool addToBuyerArr(Buyer* new_buyer);*/   //  # Nir: Replaced by operator += 
	/*2*/
	/*bool addToSellerArr(Seller* new_seller);*/     // # Nir: Should be replaced by operator += 
	/*3*/
	bool addProductToSeller(Product* prod, const char* seller_username);
	/*4*/
	bool addFeedbackToSeller(const char* buyer_username, const char* seller_username, FeedBack* feedback);
	/*5*/
	bool addProductToBuyersCart(const char* prod_name, const char* buyer_username);
	/*6*/
	bool newOrder(const char* buyer_username);
	/*7*/
	bool payment(const char* buyer_username);
	/*8*/
	void printBuyers()const;
	/*9*/
	void printSellers()const;
	/**/
	void printBuyerSellers()const;
	/*10*/
	void printAllSpecificProduct(const char* name_to_find) const;

	// Print:
	void interactiveMenu();

};

#endif // !__System_h