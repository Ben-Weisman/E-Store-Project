#include "FeedBack.h"


bool FeedBack::setFeedbackEval(char* eval)
{
	if (strlen(eval) == 0)
		return false;
	m_feedback_evaluation = strdup(eval);
	return true;
}

bool FeedBack::setFeedbackProvider(Buyer* provider)
{
	if (!provider)
		return false;
	m_feedback_provider = provider;
	return true;
}


inline const char* FeedBack::getFeedbackEvaluation()const { return m_feedback_evaluation; }
inline const Date FeedBack::getFeedbackDate()const { return m_date; }
inline const Buyer* FeedBack::getBuyer()const { return m_feedback_provider; }

void FeedBack::showFeedback()const
{
	cout << "Date provided: " << this->getFeedbackDate()->printDate() << endl;
	cout << "Provided by: " << this->getBuyer()->getFirstName() <<
		" " << this->getBuyer()->getLastName() << endl;
	cout << "Feedback: " << this->getFeedbackEvaluation();
}

FeedBack::FeedBack(char* feedback, Buyer* buyer, const Date& date): m_date(date) //c'tor
{
	setFeedbackEval(feedback);
	setFeedbackProvider(buyer);
}

FeedBack::~FeedBack() //d'tor
{
	delete[]m_feedback_evaluation;
}

FeedBack::FeedBack(FeedBack& f) //copy c'tor
{
	setFeedbackProvider(buyer);
	setFeedbackEval(f.getFeedbackEvaluation());
	m_date = f.getFeedbackDate();
}






