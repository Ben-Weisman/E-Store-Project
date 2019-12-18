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
	cin.ignore();

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
	cout << "\nCategory:\n1)Kids\n2)Electricity\n3)Office\n4)Clothing\n";
	cin >> temp;
	cin.ignore();
	category = (Product::ecategory)(temp - 1);

	
	char name[MAX_NAMES_LEN];
	cout << "Name of the product: ";
	cin.getline(name, MAX_NAMES_LEN);

	int price;
	cout << "Price: ";
	cin >> price;
	cin.ignore();

	return new Product(category, name, price, seller_username); //Ben we need to check that here the function overloading works (because i didnt sent pointer to seler)
}


Date createDate()
{
	cin.ignore();
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
	cin.ignore();
	char feedback[MAX_NAMES_LEN];
	cout << "Please write your feedback:\n ";
	cin.getline(feedback, MAX_FEEDBACK_LEN); // Do we want do seek for an option to write free text (with few lines? LUXURY)

	return new FeedBack(feedback, b_username, createDate());
}


// General note: I think we should consult about the order of the input's.. 
// Example: Does it make sence to get the addess after username?, or feedback before date? 