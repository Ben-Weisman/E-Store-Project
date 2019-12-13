#ifndef __FeedBack_h
#define __FeedBack_h
#include <string.h>

class FeedBack
{
private:
	char* m_fname; //Static or pointer?
	char* m_lname; //Static or pointer?
	char* m_feedback_date; //Static or pointer?
	char* m_feedback_evaluation; //Static or pointer?
	int m_feedback_stars; // 1-5. 1-> terrible || 5 -> great.

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
