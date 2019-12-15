#ifndef __Source_h
#define __Source_h

#include "Utils.h"
#include "Seller.h"
#include "Buyer.h"
#include "Date.h"
#include "FeedBack.h"
#include "Address.h"

const int MAX_NAMES_LEN = 30;
const int MAX_FEEDBACK_LEN = 90;

Address createAdress();
Buyer* createBuyer();
Seller* createSeller();
Product* createProduct(char* seller_username);
Date createDate();
FeedBack* createFeedback(const char* b_username);

#endif // !__Source_h