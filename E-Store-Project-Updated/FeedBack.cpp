#include "FeedBack.h"
#include <iostream>

using namespace std;
#pragma warning(disable:4996) 


// --------------------- C'tor, Copy C'tor, D'tor, Move C'tor ---------------------

FeedBack::FeedBack(char* feedback, const char* provider_username, const Date& date) : m_date(date) //c'tor
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
}

FeedBack::FeedBack(FeedBack&& f) : m_date(f.m_date) // move c'tor
{
	m_feedback_evaluation = f.m_feedback_evaluation;
	m_provider_username = f.m_provider_username;

	f.m_feedback_evaluation = nullptr;
	f.m_provider_username = nullptr;
}

// ---------------------------------------------------------------

// --------------------- Private Setters Methods ---------------------
bool FeedBack::setFeedbackEval(const char* eval)
{ // Set feedback evaluation. Validation check - not an empty string.
	if (strlen(eval) == 0)
		return false;
	m_feedback_evaluation = strdup(eval);
	return true;
}

bool FeedBack::setFeedbackProvider(const char* provider_username)
{ // Set feedback's provider username. Validation check - not an empty string.
	if (!provider_username)
		return false;
	m_provider_username = strdup(provider_username);
	return true;
}

// -----------------------------------------------------------

// --------------------- Getters Methods ---------------------
const char* FeedBack::getFeedbackEvaluation()const { return m_feedback_evaluation; }
const Date FeedBack::getFeedbackDate()const { return m_date; }
const char* FeedBack::getProviderUsername()const { return m_provider_username; }

// ---------------------------------------------------------------

void FeedBack::showFeedback()const
{ // Print Feedback. 
	cout << "Date provided: ";
	this->m_date.showDate();
	cout << endl;

	cout << "Provided by: " << m_provider_username << endl;

	this->getFeedbackEvaluation();
}





