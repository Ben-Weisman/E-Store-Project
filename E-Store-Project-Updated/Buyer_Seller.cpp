#include "Buyer_Seller.h"

Buyer_Seller::Buyer_Seller(const Buyer& b, const Seller& s) : User(b),
Seller(s), Buyer(b) {} // #### Check why when sending User(s), there's an error. 

const Buyer_Seller& Buyer_Seller::operator=(const Buyer_Seller& other)
{
	User::operator=(other);
	Buyer::operator=(other);
	Seller::operator=(other);
}

void Buyer_Seller::toOs(ostream& os)const
{
	os << typeid(*this).name() + 6;
}
