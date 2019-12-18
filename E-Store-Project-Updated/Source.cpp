#include "Source.h"
#include <iostream>

using namespace std;


Address createAdress()
{
	cleanBuffer();
	char country[MAX_NAMES_LEN];
	cout << "Country: ";
	cin.getline(country, MAX_NAMES_LEN);

	cleanBuffer();
	char city[MAX_NAMES_LEN];
	cout << "\nCity: ";
	cin.getline(city, MAX_NAMES_LEN);

	cleanBuffer();
	char street[MAX_NAMES_LEN];
	cout << "\nStreet: ";
	cin.getline(street, MAX_NAMES_LEN);

	int house_number;
	cout << "\nStreet: ";
	cin >> house_number;

	return Address(country, city, street, house_number);
}

Buyer* createBuyer()
{
	cleanBuffer();
	char f_name[MAX_NAMES_LEN];
	cout << "First name: ";
	cin.getline(f_name, MAX_NAMES_LEN);

	cleanBuffer();
	char l_name[MAX_NAMES_LEN];
	cout << "\nLast name: ";
	cin.getline(l_name, MAX_NAMES_LEN);

	cleanBuffer();
	char user_name[MAX_NAMES_LEN];
	cout << "\nUserName: ";
	cin.getline(user_name, MAX_NAMES_LEN);

	cleanBuffer();
	char pass[MAX_NAMES_LEN];
	cout << "\nPassword: ";
	cin.getline(user_name, MAX_NAMES_LEN);


	return new Buyer(user_name, pass, f_name, l_name, createAdress());
}

Seller* createSeller()
{
	cleanBuffer();
	char f_name[MAX_NAMES_LEN];
	cout << "First name: ";
	cin.getline(f_name, MAX_NAMES_LEN);

	cleanBuffer();
	char l_name[MAX_NAMES_LEN];
	cout << "\nLast name: ";
	cin.getline(l_name, MAX_NAMES_LEN);

	cleanBuffer();
	char user_name[MAX_NAMES_LEN];
	cout << "\nUserName: ";
	cin.getline(user_name, MAX_NAMES_LEN);

	cleanBuffer();
	char pass[MAX_NAMES_LEN];
	cout << "\nPassword: ";
	cin.getline(user_name, MAX_NAMES_LEN);


	return new Seller(user_name, pass, f_name, l_name, createAdress());
}

Product* createProduct(char* seller_username)
{
	Product::ecategory category;
	int temp;
	cout << "\nCategory:\n1)Kids\n2)Electricity\n3)Office\n4)Clothing\n";
	cin >> temp;
	category = (Product::ecategory)(temp - 1);

	cleanBuffer();
	char name[MAX_NAMES_LEN];
	cout << "Name of the product: ";
	cin.getline(name, MAX_NAMES_LEN);

	int price;
	cout << "\nPrice: ";
	cin >> price;

	return new Product(category, name, price, seller_username); //Ben we need to check that here the function overloading works (because i didnt sent pointer to seler)
}


Date createDate()
{
	cleanBuffer();
	int day, month, year;
	cin >> day;
	cout << "/";
	cin >> month;
	cout << "/";
	cin >> year;
	cout << endl;

	return Date(day, month, year);
}

FeedBack* createFeedback(const char* b_username)
{
	cleanBuffer();
	char feedback[MAX_NAMES_LEN];
	cout << "Please write your feedback:\n ";
	cin.getline(feedback, MAX_FEEDBACK_LEN); // Do we want do seek for an option to write free text (with few lines? LUXURY)

	return new FeedBack(feedback, b_username, createDate());
}


// General note: I think we should consult about the order of the input's.. 
// Example: Does it make sence to get the addess after username?, or feedback before date? 