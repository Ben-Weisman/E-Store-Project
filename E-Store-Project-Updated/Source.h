#ifndef __Source_h
#define __Source_h

#include "System.h"
#include "Utils.h"
#include <string>


Address createAdress();
Buyer* createBuyer(); 
Seller* createSeller(); 
Buyer_Seller* createBuyerSeller();
Product* createProduct(const string& seller_username);
Date createDate();
FeedBack* createFeedback(const string& b_username);

#endif // !__Source_h