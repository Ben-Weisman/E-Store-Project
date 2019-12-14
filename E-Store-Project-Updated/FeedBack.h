#ifndef __FeedBack_h
#define __FeedBack_h
#include <string.h>
#include "Buyer.h"
#include "Date.h"

class FeedBack
{
private:

	char* m_feedback_evaluation; 
	Buyer* m_feedback_provider;
	Date m_date;

private:
	bool setFeedbackEval(char* eval);
	bool setFeedbackProvider(Buyer* provider);

public:
	inline const char* getFeedbackEvaluation()const;
	inline const Date getFeedbackDate()const;
	inline const Buyer* getBuyer()const;

	void showFeedback()const;

	FeedBack(char* feedback, Buyer* buyer, const Date& date); //c'tor
	~FeedBack(); //d'tor
	FeedBack(FeedBack& f); //copy c'tor
};

#endif// __FeedBack_h
