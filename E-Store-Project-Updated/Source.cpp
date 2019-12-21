#include "Source.h"
#include <iostream>

using namespace std;


Address createAdress()
{
	char country[MAX_NAMES_LEN];
	cout << "Country: ";
	cin.getline(country, MAX_NAMES_LEN);

	char city[MAX_NAMES_LEN];
	cout << "City: ";
	cin.getline(city, MAX_NAMES_LEN);

	char street[MAX_NAMES_LEN];
	cout << "Street: ";
	cin.getline(street, MAX_NAMES_LEN);

	int house_number;
	cout << "House number: ";
	cin >> house_number;
	cin.ignore(1,'\n');

	return Address(country, city, street, house_number);
}

Buyer* createBuyer()
{
	char f_name[MAX_NAMES_LEN];
	cout << "First name: ";
	cin.getline(f_name, MAX_NAMES_LEN);
	

	char l_name[MAX_NAMES_LEN];
	cout << "Last name: ";
	cin.getline(l_name, MAX_NAMES_LEN);


	char user_name[MAX_NAMES_LEN];
	cout << "UserName: ";
	cin.getline(user_name, MAX_NAMES_LEN);

	
	char pass[MAX_NAMES_LEN];
	cout << "Password: ";
	cin.getline(pass, MAX_NAMES_LEN);


	return new Buyer(user_name, pass, f_name, l_name, createAdress());
}

Seller* createSeller()
{
	char f_name[MAX_NAMES_LEN];
	cout << "First name: ";
	cin.getline(f_name, MAX_NAMES_LEN);

	
	char l_name[MAX_NAMES_LEN];
	cout << "Last name: ";
	cin.getline(l_name, MAX_NAMES_LEN);


	char user_name[MAX_NAMES_LEN];
	cout << "UserName: ";
	cin.getline(user_name, MAX_NAMES_LEN);

	
	char pass[MAX_NAMES_LEN];
	cout << "Password: ";
	cin.getline(pass, MAX_NAMES_LEN);


	return new Seller(user_name, pass, f_name, l_name, createAdress());
}

Product* createProduct(char* seller_username)
{
	Product::ecategory category;
	int temp;
	cout << endl << "Category:" << endl << "1)Kids" << endl << "2)Electricity" << endl << "3)Office" << endl << "4)Clothing" << endl;
	cin >> temp;
	cin.ignore(1,'\n');
	category = (Product::ecategory)(temp - 1);

	
	char name[MAX_NAMES_LEN];
	cout << "Name of the product: ";
	cin.getline(name, MAX_NAMES_LEN);

	double price;
	cout << "Price: ";
	cin >> price;
	cin.ignore(1,'\n');

	return new Product(category, name, price, seller_username); 
}


Date createDate()
{
	int day, month, year;
	cout << " - day: ";
	cin >> day;
	cout << " - month: ";
	cin >> month;
	cout << " - year: ";
	cin >> year;
	cout << endl;
	cin.ignore(1,'\n');

	return Date(day, month, year);
}

FeedBack* createFeedback(const char* b_username)
{
	
	char feedback[MAX_FEEDBACK_LEN];
	cout << "Please write your feedback: ";

	cin.getline(feedback, MAX_FEEDBACK_LEN);

	return new FeedBack(feedback, b_username, createDate());
}
