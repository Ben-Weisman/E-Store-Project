#include "Source.h"
#include <iostream>

using namespace std;

Address createAdress()
{// creating address
	string country;
	cout << "For space-seperated cities / countries, please enter a '-'" << endl;
	cout << "Country: ";
	getline(cin, country);

	string city;
	cout << "City: ";
	getline(cin, city);

	string street;
	cout << "Street: ";
	getline(cin, street);

	int house_number;
	do {
	cout << "House number: ";
	cin >> house_number;
	cin.ignore(1, '\n');
	} while (house_number < 1);

	return Address(country, city, street, house_number);
}

Buyer_Seller* createBuyerSeller()
{ //creating buyer-seller
	string f_name;
	cout << "First name: ";
	getline(cin, f_name);


	string l_name;
	cout << "Last name: ";
	getline(cin, l_name);


	string user_name;
	cout << "UserName: ";
	getline(cin, user_name);


	string pass;
	cout << "Password: ";
	getline(cin, pass);

	Address a = createAdress();

	return new Buyer_Seller(Buyer(user_name, pass, f_name, l_name, a), Seller(user_name, pass, f_name, l_name, a));
}

Buyer* createBuyer()
{//creating buyer
	string f_name;
	cout << "First name: ";
	getline(cin, f_name);
	

	string l_name;
	cout << "Last name: ";
	getline(cin, l_name);


	string user_name;
	cout << "UserName: ";
	getline(cin, user_name);

	
	string pass;
	cout << "Password: ";
	getline(cin, pass);


	return new Buyer(user_name, pass, f_name, l_name, createAdress());
}

Seller* createSeller()
{//creating seller
	string f_name;
	cout << "First name: ";
	getline(cin, f_name);

	
	string l_name;
	cout << "Last name: ";
	getline(cin, l_name);


	string user_name;
	cout << "UserName: ";
	getline(cin, user_name);

	
	string pass;
	cout << "Password: ";
	getline(cin, pass);


	return new Seller(user_name, pass, f_name, l_name, createAdress());
} 

Product* createProduct(const string& seller_username)
{//creating product
	Product::ecategory category;
	int temp;
	cout << endl << "Category:" << endl << "1)Kids" << endl << "2)Electricity" << endl << "3)Office" << endl << "4)Clothing" << endl;
	cin >> temp;
	cin.ignore(1, '\n');
	category = (Product::ecategory)(temp - 1);

	
	string name;
	cout << "Name of the product: ";
	getline(cin, name);

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
	string date;
	int day, month, year;

	cout << "Enter date in this format: dd/mm/yyyy" << endl;
	cin >> date;

	day = ((date[0] - '0') * 10) + (date[1] - '0'); //calculation of day
	month = ((date[3] - '0') * 10) + (date[4] - '0'); //calculation of month
	year = ((date[6] - '0') * 1000) + ((date[7] - '0') * 100) + ((date[8] - '0') * 10) + (date[9] - '0');//calculation of year

	return Date(day, month, year);

}

FeedBack* createFeedback(const string& b_username)
{//creating feedback
	string feedback;
	cout << "Please write your feedback: ";
	getline(cin, feedback);

	return new FeedBack(feedback, b_username, createDate());
}
