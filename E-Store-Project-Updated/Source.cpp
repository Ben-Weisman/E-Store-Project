#include "Source.h"
#include <iostream>

using namespace std;
#pragma warning(disable:4996) 


Address createAdress()
{// creating address
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
	do {
	cout << "House number: ";
	cin >> house_number;
	cin.ignore(1,'\n');
	} while (house_number < 1);

	return Address(country, city, street, house_number);
}

Buyer_Seller* createBuyerSeller()
{ //creating buyer-seller
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

	Address a = createAdress();

	return new Buyer_Seller(Buyer(user_name, pass, f_name, l_name, a), Seller(user_name, pass, f_name, l_name, a));
}

Buyer* createBuyer()
{//creating buyer
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
{//creating seller
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
{//creating product
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
	do {
		cout << "Price: ";
		cin >> price;
		cin.ignore(1, '\n');
	} while (price<1);

	return new Product(category, name, price, seller_username); 
}


Date createDate()
{//creating date
	char date[DATE_STRING_LEN];
	char* day, *month, *year;

	cout << "Enter date in this format: dd/mm/yyyy" << endl;
	cin.getline(date, DATE_STRING_LEN);

	day = strtok(date, "/");
	month = strtok(nullptr, "/");
	year = strtok(nullptr, "\0");

	return Date(atoi(day), atoi(month), atoi(year));

}

FeedBack* createFeedback(const char* b_username)
{//creating feedback
	char feedback[MAX_FEEDBACK_LEN];
	cout << "Please write your feedback: ";
	cin.getline(feedback, MAX_FEEDBACK_LEN);

	return new FeedBack(feedback, b_username, createDate());
}
