#ifndef __System_h
#define __System_h 

#include "Seller.h"
#include "Buyer.h"
//#include "Product.h"

const int MAX_LEN = 20;
const int NOT_EXIST = -1;
const int EXIT = -1;
const int MAX_TRIES = 3;

class System
{
private:
	const char* m_name; //System name

	Seller** m_seller_arr; // Sellers array
	int m_sellers_phy_size; // Sellers array physic size
	int m_num_of_sellers; // Sellers array logic size


	Buyer** m_buyer_arr; // Buyers array
	int m_buyers_phy_size; // Sellers array physic size
	int m_num_of_buyers; // Sellers array logic size


private:
	System(const System&) = default; // Under private cause we don't want anyone to duplicate our system  ----> delete is beter option?

public:
	System(const char* name); //c'tor
	~System();// d'tor

public:
	bool setName(const char* name);

	bool setNumOfSellers(int num_of_sellers);
	bool setSellersPhySize(int physize);

	bool setNumOfBuyers(int num_of_buyers);
	bool setBuyersPhySize(int physize);

public:
	inline const char* getName()const{ return m_name; }
	inline  Seller** getSellerArr()const{ return m_seller_arr; }
	inline  int getSellersPhySize()const{ return m_sellers_phy_size; }
	inline  int getNumOfSellers()const{ return m_num_of_sellers; }
	inline  Buyer** getBuyerArr()const{ return m_buyer_arr; }
	inline  int getBuyersPhySize()const{ return m_buyers_phy_size; }
	inline  int getNumOfBuyers()const{ return m_num_of_buyers; }


	// ---------------------------------- maintanance functions ------------------------------------

	const int isBuyerExist(const char* buyer_username)const;
	void buyersRealloc();
	const int isSellerExist(const char* seller_username)const;
	void sellersRealloc();


	 // ---------------------------------- MENU functions ------------------------------------

public:
	/*1*/                                       
	bool addToBuyerArr(Buyer* new_buyer);
	/*2*/
	bool addToSellerArr(Seller* new_seller);
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
	/*10*/
	void printAllSpecificProduct(const char* name_to_find) const;

};

#endif // !__System_h