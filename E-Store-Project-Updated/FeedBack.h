#ifndef __FeedBack_h
#define __FeedBack_h
#include "Buyer.h"
#include "Date.h"

class FeedBack
{
private:

	char* m_feedback_evaluation;
	char* m_provider_username;
	Date m_date;

private:
	bool setFeedbackEval(const char* eval);
	bool setFeedbackProvider(const char* provider_username);

public:
	FeedBack(char* feedback, const char* provider_username, const Date& date); //c'tor
	~FeedBack(); //d'tor
	FeedBack(const FeedBack& f); //copy c'tor
	FeedBack(FeedBack&& f); // move c'tor

public: 

	inline const char* getFeedbackEvaluation()const { return m_feedback_evaluation; }
	inline const Date& getFeedbackDate()const { return m_date; }
	inline const char* getProviderUsername()const { return m_provider_username; }

	void showFeedback()const;

	friend ostream& operator<<(ostream& os, FeedBack& feedback);

};

#endif// __FeedBack_h
