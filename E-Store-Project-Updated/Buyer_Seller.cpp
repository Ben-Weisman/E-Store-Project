#include "Buyer_Seller.h"



// -------------------- c'tor -------------------- //

Buyer_Seller::Buyer_Seller(const Buyer& b, const Seller& s) : User(s),
Seller(s), Buyer(b) {}

Buyer_Seller::Buyer_Seller(ifstream& in_file):User(in_file), Buyer(in_file), Seller (in_file){}

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



