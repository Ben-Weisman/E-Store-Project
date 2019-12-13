#ifndef __Source_h
#define __Source_h

#include "Buyer.h"
#include "Seller.h"
#include "Address.h"

const int MAX_LEN = 50;

Address createAdress();
Buyer* createBuyer();
Seller* createSeller();
Product* createProduct();
Feedback* createFeedback();

#endif // !__Source_h