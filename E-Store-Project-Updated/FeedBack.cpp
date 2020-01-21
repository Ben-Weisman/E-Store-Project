#include "FeedBack.h"
#include <iostream>
#include <string>
using namespace std;
#pragma warning(disable:4996) 


// --------------------- C'tor, Copy C'tor, D'tor, Move C'tor ---------------------

FeedBack::FeedBack(string& feedback, const string& provider_username, const Date& date) : m_date(date) //c'tor
{
	setFeedbackEval(feedback);
	setFeedbackProvider(provider_username);
}

FeedBack::FeedBack(const FeedBack& other) :m_date(other.m_date) //copy c'tor
{ // Don't call the assignment operator because it's assigning date, and we want to keep
	// the call in the init list. - After consulting with the lecturer.

	setFeedbackEval(other.m_feedback_evaluation);
	setFeedbackProvider(other.m_provider_username);
}

FeedBack::FeedBack(FeedBack&& f) : m_date(f.m_date) // move c'tor
{
	m_feedback_evaluation = f.m_feedback_evaluation;
	m_provider_username = f.m_provider_username;

	f.m_feedback_evaluation = nullptr;
	f.m_provider_username = nullptr;
}


// --------------------- Private Setters Methods ---------------------

bool FeedBack::setFeedbackEval(const string& eval)
{ // Set feedback evaluation. Validation check - not an empty string.
	if (eval.length() == 0)
		return false;
	m_feedback_evaluation = eval;
	return true;
}

bool FeedBack::setFeedbackProvider(const string& provider_username)
{ // Set feedback's provider username. Validation check - not an empty string.
	if (provider_username.length() == 0)
		return false;
	m_provider_username = provider_username;
	return true;
}


// ---------------------------printing methods------------------------------------

void FeedBack::showFeedback()const
{ // Print Feedback. 
	cout << "Date provided: ";
	m_date.showDate();
	cout << endl;

	cout << "Provided by: " << m_provider_username << endl;

	this->getFeedbackEvaluation();
}

ostream& operator<<(ostream& os, FeedBack& feedback)
{
	os << "Provided by: " << feedback.m_provider_username << "\nThe feedback:\n" << feedback.m_feedback_evaluation
		<< endl;
	return os;
}
const FeedBack& FeedBack::operator=(const FeedBack& other)
{ 
	if (this != &other)
	{
		setFeedbackEval(other.m_feedback_evaluation);
		setFeedbackProvider(other.m_provider_username);
		m_date = other.m_date;
	}
	return *this;
}




