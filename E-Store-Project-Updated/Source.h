#ifndef __Source_h
#define __Source_h

#include "Utils.h"
#include "Seller.h"
#include "Buyer.h"
#include "Date.h"
#include "FeedBack.h"

const int MAX_NAMES_LEN = 30;
const int MAX_FEEDBACK_LEN = 90;

Address& createAdress();
Buyer* createBuyer();
Seller* createSeller();
Product* createProduct();
Date& createDate();
FeedBack* createFeedback();

#endif // !__Source_h