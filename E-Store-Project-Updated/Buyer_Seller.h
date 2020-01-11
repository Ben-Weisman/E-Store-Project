#ifndef __Buyer_Seller_h
#define __Buyer_Seller_h
#include <iostream>
#include "Buyer.h"
#include "Seller.h"
#include "User.h"

using namespace std;

class Buyer_Seller : public Buyer, public Seller
{
public:
	Buyer_Seller(const Buyer &b, const Seller &s); //##Nir: maybe we should change, according to System.cpp line 490  
	~Buyer_Seller();
	Buyer_Seller(const Buyer_Seller& bs);


};

#endif // !__Buyer_Seller_h