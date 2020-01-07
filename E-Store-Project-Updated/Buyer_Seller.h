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
	Buyer_Seller(const Seller &s,const Buyer &b);
	~Buyer_Seller();
	Buyer_Seller(const Buyer_Seller& bs);


};

#endif // !__Buyer_Seller_h