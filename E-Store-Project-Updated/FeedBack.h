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
	//			Setters			//
	// No option for re-assigning the following attributes after initialization -
	//thus declared as private.
	bool setFeedbackEval(const char* eval);
	bool setFeedbackProvider(const char* provider_username);

public:
	//			c'tor, copy c'tor, d'tor, move c'tor			//
	FeedBack(char* feedback, const char* provider_username, const Date& date); //c'tor
	~FeedBack(); //d'tor
	FeedBack(const FeedBack& f); //copy c'tor
	FeedBack(FeedBack&& f); // move c'tor

public: 
	//			Getters			//
	inline const char* getFeedbackEvaluation()const { return m_feedback_evaluation; }
	inline const Date& getFeedbackDate()const { return m_date; }
	inline const char* getProviderUsername()const { return m_provider_username; }

	//			Print method			//
	void showFeedback()const;

	//			Operators			//
	friend ostream& operator<<(ostream& os, FeedBack& feedback);
	const FeedBack& operator=(const FeedBack& other);


};

#endif// __FeedBack_h
