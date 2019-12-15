//                                         --      Ofek The Officer     --

#include "System.h"
#include "Buyer.h"
#include "Source.h"
#include <iostream>
using namespace std;

const int MAX_NAMES_LEN = 20;

// We should move all this to Menu File 

int main()
{
	System system("eben");
	
	bool exit_flag = true;
	while (exit_flag)
	{
		int i = 1;
		cout << "Actions menu:\n";
		cout << (i++) << ") Add buyer\n";
		cout << (i++) << ") Add seller\n";
		cout << (i++) << ") Add product\n";
		cout << (i++) << ") Add feedback\n";
		cout << (i++) << ") Add to cart\n";
		cout << (i++) << ") Order products\n";
		cout << (i++) << ") Payment\n";
		cout << (i++) << ") Show all buyers\n";
		cout << (i++) << ") Show all sellers\n";
		cout << (i++) << ") Show all products with you choosen name\n";
		cout << (i++) << ") Exit\n\n";
		cout << "Please enter your action: ";
		int option;
		cin >> option;
		
		switch (option)
		{
		case 1://add buyer

			if (!(system.addToBuyerArr(createBuyer())))
				cout << "Username already exist, please try again";
			break;

		case 2://add seller

			if (!(system.addToSellerArr(createSeller())))
				cout << "Username already exist, please try again";
			break;

		case 3: //add product to seller
			char seller_username[MAX_NAMES_LEN];
			cout << "Enter the username of the seller: ";
			cin >> seller_username;

			if(system.addProductToSeller(createProduct(seller_username), seller_username)==false)
				cout << "No such seller username."; 
			//Should we free the prod? *********************************************************************************
			break;

		case 4: //add feedback to seller 
			char b_username[MAX_NAMES_LEN];
			cout << "Enter buyer's username: ";
			cin >> b_username;

			char s_username[MAX_NAMES_LEN];
			cout << "Enter seller's username: ";
			cin >> s_username;

			if(system.addFeedbackToSeller(b_username, s_username, createFeedback(b_username))==false)
				cout << "No such seller or buyer username."; //LUXURY ------> which of them was missing
			break;

		case 5:
			char username[MAX_NAMES_LEN];
			cout << "\nEnter the username of the buyer: ";
			cin >> username;

			char prod_name[MAX_NAMES_LEN];
			cout << "\nEnter the product name: ";
			cin >> prod_name;

			system.addProductToBuyersCart(prod_name, username);
			break;

		case 6:
			//order
			char b_username[MAX_NAMES_LEN];
			cout << "Enter the username of the buyer:";
			cin >> b_username;

			char s_username[MAX_NAMES_LEN];
			cout << "Enter the username of the seller:";
			cin >> s_username;

			system.newOrder(b_username, s_username);
		case 7:
			//pay
		case 8:
			system.printBuyers();
		case 9:
			system.printSellers();
		case 10:
			//show specific product
		case 11:
			exit_flag = false;
			break;
		default:
			cout << "Ops... No such action\n\n";
			break;
		}

	}

	return 0;
}