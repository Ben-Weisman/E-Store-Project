#include "Source.h"
#include "Utils.h"
#include <iostream>
using namespace std;


Address createAdress()
{
	cleanBuffer();
	char country[MAX_LEN];
	cout << "Country: ";
	cin.getline(country, MAX_LEN);

	cleanBuffer();
	char city[MAX_LEN];
	cout << "\nCity: ";
	cin.getline(city, MAX_LEN);

	cleanBuffer();
	char street[MAX_LEN];
	cout << "\nStreet: ";
	cin.getline(street, MAX_LEN);

	cleanBuffer();
	int house_number;
	cout << "\nStreet: ";
	cin >> house_number;

	return(Address a(country, city, street, house_number));
}

Buyer* createBuyer() //Waiting for Ben Buyer file (:
{
	cleanBuffer();
	char f_name[MAX_LEN];
	cout << "First name: ";
	cin.getline(f_name, MAX_LEN);

	cleanBuffer();
	char l_name[MAX_LEN];
	cout << "\nLast name: ";
	cin.getline(l_name, MAX_LEN);

	Address adress = createAdress();

	cleanBuffer();
	char user_name[MAX_LEN];
	cout << "\nUserName: ";
	cin.getline(user_name, MAX_LEN);

	// more attributes

	Buyer* b = new Buyer(/*constractor*/); // <------ Ben

	return b;
}

Seller* createSeller() //Waiting for Ben Seller file (:
{
	cleanBuffer();
	char f_name[MAX_LEN];
	cout << "First name: ";
	cin.getline(f_name, MAX_LEN);

	cleanBuffer();
	char l_name[MAX_LEN];
	cout << "\nLast name: ";
	cin.getline(l_name, MAX_LEN);

	Address adress = createAdress();

	cleanBuffer();
	char user_name[MAX_LEN];
	cout << "\nUserName: ";
	cin.getline(user_name, MAX_LEN);

	// more attributes

	Seller* s = new Seller(/*constractor*/);

	return b;
}

Product* createProduct()
{
	cleanBuffer();
	Product::ecategory category;
	int temp;
	cout << "\nCategory:\n1)Kids\n2)Electricity\n3)Office\n4)Clothing\n";
	cin >> temp;
	category = (Product::ecategory)(temp - 1);

	cleanBuffer();
	char name[MAX_LEN];
	cout << "Name: ";
	cin.getline(name, MAX_LEN);

	//cleanBuffer(); Do we need ????
	int price;
	cout << "\nPrice: ";
	cin >> price;
	Product* p = new Product(category, name, price); // Can i initilize that way?
	return p;
}

Feedback* createFeedback()
{
	//Date
	//Text
	//...
	Feedback* fb = new Feedback(/*Waiting for Ben the king*/);
	return fb;
}