#ifndef __Buyer_Seller_h
#define __Buyer_Seller_h
#include <iostream>
#include "Buyer.h"
#include "Seller.h"

using namespace std;

class Buyer_Seller : public Seller, public Buyer
{
public:
	// No need for overriding the default copy c'tor & d'tor - No allocated data members in this class.
	Buyer_Seller(const Buyer& b, const Seller& s);   // c'tor
	Buyer_Seller(ifstream& in_file);

	//			Operators			//
	const Buyer_Seller& operator=(const Buyer_Seller& other); 
	virtual void toOs(ostream& os)const;
};

#endif // !__Buyer_Seller_h