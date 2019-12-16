#include "FeedBack.h"
#include <iostream>
using namespace std;

bool FeedBack::setFeedbackEval(const char* eval)
{
	if (strlen(eval) == 0)
		return false;
	m_feedback_evaluation = strdup(eval);
	return true;
}

bool FeedBack::setFeedbackProvider(const char* provider_username)
{
	if (!provider_username)
		return false;
	m_provider_username = strdup(provider_username);
	return true;
}


inline const char* FeedBack::getFeedbackEvaluation()const { return m_feedback_evaluation; }
inline const Date FeedBack::getFeedbackDate()const { return m_date; }
inline const char* FeedBack::getProviderUsername()const { return m_provider_username; }

void FeedBack::showFeedback()const // Nir: there was a lot of mess here, Every clss have his Show method, we should use them.
{
	cout << "Date provided: ";
	this->m_date.showDate();      // Nir: I changed it from "cout<<printFeedbackDate->printDate" **************************************************************************************************************
	cout << endl;

	cout << "Provided by: " << m_provider_username << endl;	
	
	this->getFeedbackEvaluation();
}

FeedBack::FeedBack(char* feedback, const char* provider_username, const Date& date): m_date(date) //c'tor
{
	setFeedbackEval(feedback);
	setFeedbackProvider(provider_username);
}

FeedBack::~FeedBack() //d'tor
{
	delete[]m_feedback_evaluation;
	delete[]m_provider_username;
}

FeedBack::FeedBack(const FeedBack& f) :m_date(f.m_date) //copy c'tor
{
	setFeedbackProvider(m_provider_username);
	setFeedbackEval(f.getFeedbackEvaluation());
	//m_date = f.getFeedbackDate(); ************Nir: This line is a mistake. Contained Object should be initilized in the initline ^
}

// We can write a move c'tor 




