#include "System.h"
#include "Source.h"
#include <iostream>
using namespace std;

#pragma warning(disable:4996) 

// We should move all this to Menu File 

int main()
{
	System system("eben");

	bool exit_flag = true;
	while (exit_flag)
	{
		int i = 1;
		cout << "----------------------------------------------------------Actions menu:----------------------------------------------------------"<< endl;
		cout << (i++) << ") Add buyer"<< endl;
		cout << (i++) << ") Add seller"<< endl;
		cout << (i++) << ") Add product to seller"<< endl;
		cout << (i++) << ") Add feedback" << endl;
		cout << (i++) << ") Add to cart"<< endl;
		cout << (i++) << ") Order products"<< endl;
		cout << (i++) << ") Payment"<< endl;
		cout << (i++) << ") Show all buyers"<< endl;
		cout << (i++) << ") Show all sellers"<< endl;
		cout << (i++) << ") Show all products with you chosen name"<< endl;
		cout << (i++) << ") Exit" << endl << endl;
		cout << "Please enter your action: ";
		int option;
		cin >> option;
		cin.ignore(1,'\n');

		switch (option)
		{
			char b_username[MAX_NAMES_LEN];
			char s_username[MAX_NAMES_LEN];
			char prod_name[MAX_NAMES_LEN];
			int b_index; // Latest update.
		
		case 1://add buyer

			if (!(system.addToBuyerArr(createBuyer())))
				cout << "Username already exist, please try again"<< endl;
			break;
		
		case 2://add seller

			if (!(system.addToSellerArr(createSeller())))
				cout << "Username already exist, please try again"<< endl;
			break;
		
		case 3: //add product to seller
			cout << "Enter the username of the seller: ";
			cin.getline(s_username,MAX_NAMES_LEN);
			Product* p;
			if (system.addProductToSeller(p = createProduct(s_username), s_username) == false)
			{
				cout << "No such seller username." << endl;
				delete p; 
			}

			break;
		
		case 4: //add feedback to seller 
			FeedBack * f;
			cout << "Enter buyer's username: ";
			cin.getline(b_username,MAX_NAMES_LEN);
			
			cout << "Enter seller's username: ";
			cin.getline(s_username,MAX_NAMES_LEN);
			

			// NIR Please Review this update. 
			//######## Latest update ########
			// Before creating a feedback, first check if there was indeed an 
			// order made by THIS BUYER from THIS SERLLER.
			// If so, continue with creating the feedback as usual. 
			// else, print an error message. 
			b_index = system.isBuyerExist(b_username);
			if (!system.getBuyerArr()[b_index]->isOrderedFrom(s_username))
			{
				cout << "Invalid action, " << b_username << " didn't buy from " << s_username << endl; 
			}
			else
			{
				system.addFeedbackToSeller(b_username, s_username, f = createFeedback(b_username));
				cout << "Feedback added successfully.";
			}
			//################################

			// ################ Previous version ################
			/*if (system.addFeedbackToSeller(b_username, s_username, f = createFeedback(b_username)) == false)
			{
				cout << "Invalid action, " << b_username << " didn't buy from " << s_username << endl;
				delete f; 
			}
			else
				cout << "Feedback added successfully." ;
			########################################################*/


			break;

		case 5: //add to cart
			cout << "Enter the username of the buyer: ";
			cin.getline(b_username,MAX_NAMES_LEN);

			
			cout << "Enter the product name: ";
			cin.getline(prod_name, MAX_NAMES_LEN);

			if (system.addProductToBuyersCart(prod_name, b_username) == false)
			{
				cout << "Buyer or prod not exist in the system." << endl;
			}

			break;

		case 6:	//order
			cout << "Enter the username of the buyer:";
			cin.getline(b_username,MAX_NAMES_LEN);

			system.newOrder(b_username);

			break;

		case 7:	//payment
			cout << "Enter the username of the buyer:";
			cin.getline(b_username,MAX_NAMES_LEN);

			system.payment(b_username);

			break;

		case 8: //print all buyers
			cout << endl;
			system.printBuyers();

			break;
		case 9://print all sellers
			cout << endl;
			system.printSellers();

			break;
		case 10: // print all products from specific name  
			cout << "Enter the product name: ";
			cin.getline(prod_name,MAX_NAMES_LEN);

			cout << endl;
			system.printAllSpecificProduct(prod_name);

			break;

		case 11:
			cout << "Thanks for using "<<system.getName()<<", Bye Bye (:" << endl;
			exit_flag = false;
			break;
		default:
			cout << "Ops... No such action" << endl << endl;
			break;
		}

	}

	return 0;
}