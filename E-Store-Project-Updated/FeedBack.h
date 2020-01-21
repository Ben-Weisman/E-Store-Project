#ifndef __FeedBack_h
#define __FeedBack_h
#include "Buyer.h"
#include "Date.h"
#include <string>

class FeedBack
{
private:
	string m_feedback_evaluation;
	string m_provider_username;
	Date m_date;

private:
	//			Setters			//
	// No option for re-assigning the following attributes after initialization -
	//thus declared as private.
	bool setFeedbackEval(const string& eval);
	bool setFeedbackProvider(const string& provider_username);

public:
	//			c'tor, copy c'tor, d'tor, move c'tor			//
	FeedBack(string& feedback, const string& provider_username, const Date& date); //c'tor
	FeedBack(const FeedBack& f); //copy c'tor
	FeedBack(FeedBack&& f); // move c'tor

public: 
	//			Getters			//
	inline const string getFeedbackEvaluation()const { return m_feedback_evaluation; }
	inline const Date& getFeedbackDate()const { return m_date; }
	inline const string getProviderUsername()const { return m_provider_username; }

	//			Print method			//
	void showFeedback()const;

	//			Operators			//
	friend ostream& operator<<(ostream& os, FeedBack& feedback);
	const FeedBack& operator=(const FeedBack& other);


};

#endif// __FeedBack_h
