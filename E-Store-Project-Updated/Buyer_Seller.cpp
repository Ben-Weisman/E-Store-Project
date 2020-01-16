#include "Buyer_Seller.h"
#pragma warning(disable:4996) 


// -------------------- c'tor -------------------- //

Buyer_Seller::Buyer_Seller(const Buyer& b, const Seller& s) : User(s),
Seller(s), Buyer(b) {}

 // -------------------- Operators -------------------- // 

 const Buyer_Seller& Buyer_Seller::operator=(const Buyer_Seller& other)
 {
	 Buyer::operator=(other);
	 Seller::operator=(other);
	 return *this;
 }

 void Buyer_Seller::toOs(ostream& os)const
 {
	 os << "\n\tUser type: " << typeid(*this).name() + 6;
 }



