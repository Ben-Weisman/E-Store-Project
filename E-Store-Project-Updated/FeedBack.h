#ifndef __FeedBack_h
#define __FeedBack_h
#include <string.h>
#include "Buyer.h"
#include "Date.h"

class FeedBack
{
private:
	char* m_fname;
	char* m_lname;
	char* m_feedback_date;
	char* m_feedback_evaluation; 
	int m_feedback_stars;
	Buyer* m_feedback_provider;
	Address m_address;
	Date m_date;

public:
	char* getFirstName();
	char* getLastName();
	char* getFeedbackDate();
	char* getFeedbackEvaluation();
	int getStars();

	void setFirstName(char* first_name);
	void setLastName(char* last_name);
	void setFeedbackDate(char* date);
	void setFeedbackEvaluation(char* eval);
	void setStars(int rank);

	FeedBack(char* fname = '\0', char* lname, char* date, char* eval, int star); // c'tor

};

#endif// __FeedBack_h
