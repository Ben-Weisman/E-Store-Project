#ifndef __Buyer_Seller_h
#define __Buyer_Seller_h
#include <iostream>
#include "Buyer.h"
#include "Seller.h"
#include "User.h"

using namespace std;

class Buyer_Seller : public Seller, public Buyer
{
public:
	Buyer_Seller(const Buyer& b, const Seller& s); //##Nir: maybe we should change, according to System.cpp line 490  

	const Buyer_Seller& operator=(const Buyer_Seller& bs);
	virtual void toOs(ostream& os)const {};

};

#endif // !__Buyer_Seller_h