#ifndef __System_h
#define __System_h 

#include "Seller.h"
#include "Buyer.h"
//#include "Product.h"

const int MAX_LEN = 20;
const int NOT_EXIST = -1;
const int EXIT = -1;

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
	 const char* getName()const;

	 Seller** getSellerArr()const;
	 int getSellersPhySize()const;
	 int getNumOfSellers()const;

	 Buyer** getBuyerArr()const;
	 int getBuyersPhySize()const;
	 int getNumOfBuyers()const;


	/////////////////////////////////////////////////////////////menu functions/////////////////////////////////////////////////////////////
public:
	//1
	const int isBuyerExist(const char* buyer_username)const; //the func returns the index of a specific buyer according to his username or -1 if didn't exist
	void buyersRealloc();
	bool addToBuyerArr(Buyer* new_buyer);
	//2
	const int isSellerExist(const char* seller_username)const; //the func returns the index of a specific seller according to his username or -1 if didn't exist
	void sellersRealloc();
	bool addToSellerArr(Seller* new_seller);
	//3
	bool addProductToSeller(Product* prod, const char* seller_username);
	//4
	bool addFeedbackToSeller(const char* buyer_username, const char* seller_username, FeedBack* feedback);
	//5
	bool addProductToBuyersCart(const char* prod_name, const char* buyer_username);
	//6
	bool newOrder(const char* buyer_username);
	//7
	bool payment(const char* buyer_username);
	//8
	void printBuyers()const;
	//9
	void printSellers()const;
	//10
	void printAllSpecificProduct(const char* name_to_find) const;

};

#endif // !__System_h