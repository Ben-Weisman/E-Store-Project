#include "System.h"
#include "Source.h"
#include <iostream>
using namespace std;

// We should move all this to Menu File 

int main()
{
	System system("eben");

	bool exit_flag = true;
	while (exit_flag)
	{
		int i = 1;
		cout << "\n----------------------------------------------------------Actions menu:----------------------------------------------------------\n";
		cout << (i++) << ") Add buyer\n";
		cout << (i++) << ") Add seller\n";
		cout << (i++) << ") Add product\n";
		cout << (i++) << ") Add feedback\n";
		cout << (i++) << ") Add to cart\n";
		cout << (i++) << ") Order products\n";
		cout << (i++) << ") Payment\n";
		cout << (i++) << ") Show all buyers\n";
		cout << (i++) << ") Show all sellers\n";
		cout << (i++) << ") Show all products with you chosen name\n";
		cout << (i++) << ") Exit\n\n";
		cout << "Please enter your action: ";
		int option;
		cin >> option;
		cin.ignore();

		switch (option)
		{
			char b_username[MAX_NAMES_LEN];
			char s_username[MAX_NAMES_LEN];
			char prod_name[MAX_NAMES_LEN];

		case 1://add buyer

			if (!(system.addToBuyerArr(createBuyer())))
				cout << "Username already exist, please try again\n";
			break;

		case 2://add seller

			if (!(system.addToSellerArr(createSeller())))
				cout << "Username already exist, please try again\n";
			break;

		case 3: //add product to seller
			cout << "Enter the username of the seller: ";
			cin >> s_username;
			Product* p;
			if (system.addProductToSeller(p = createProduct(s_username), s_username) == false)
			{
				cout << "No such seller username.";
				delete[]p; //Should we free the prod? *****************************************************************************************
			}
			break;

		case 4: //add feedback to seller 
			cout << "Enter buyer's username: ";
			cin >> b_username;

			cout << "Enter seller's username: ";
			cin >> s_username;
			FeedBack* f;
			if (system.addFeedbackToSeller(b_username, s_username, f = createFeedback(b_username)) == false)
			{
				cout << "Invalid action, " << b_username << "didn't buy from " << s_username << endl;
				delete[]f; //Should we free the feedback? *****************************************************************************************
			}

			break;

		case 5: //add tp cart
			cout << "\nEnter the username of the buyer: ";
			cin >> b_username;

			
			cout << "\nEnter the product name: ";
			cin >> prod_name;

			system.addProductToBuyersCart(prod_name, b_username);
			break;

		case 6:	//order
			cout << "Enter the username of the buyer:";
			cin >> b_username;

			cout << "Enter the username of the seller:";
			cin >> s_username;

			system.newOrder(b_username);
			break;
		case 7:	//payment
			cout << "Enter the username of the buyer:";
			cin >> b_username;

			system.payment(b_username);

			break;
		case 8: //print all buyers
			system.printBuyers();

			break;
		case 9://print all sellers
			system.printSellers();

			break;
		case 10: // print all products from specific name  
			cout << "\nEnter the product name: ";
			cin >> prod_name;

			system.printAllSpecificProduct(prod_name);

			break;
		case 11:
			cout << "\Thanks for using "<<system.getName()<<", Bye Bye (:";
			exit_flag = false;
			break;
		default:
			cout << "Ops... No such action\n\n";
			break;
		}

	}

	return 0;
}