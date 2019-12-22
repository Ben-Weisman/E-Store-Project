#include "System.h"
#include "Source.h"
#include "Order.h"
#include <iostream>

using namespace std;
#pragma warning(disable:4996) 

// --------------------- C'tor, D'tor ---------------------


System::System(const char* name = "eBen") //Default name
{
	setName(name);

	setSellersPhySize(1);
	setNumOfSellers(0);
	m_seller_arr = new Seller*[m_sellers_phy_size];

	setBuyersPhySize(1);
	setNumOfBuyers(0);
	m_buyer_arr = new Buyer*[m_buyers_phy_size];
}
System::~System()// d'tor
{
	delete[] m_name; //free name

	// free buyers arr: 

	for (int i = 0; i < m_num_of_buyers; i++)
		delete m_buyer_arr[i];

	delete[]m_buyer_arr;

	// free sellers arr :

	for (int i = 0; i < m_num_of_sellers; i++)
		delete m_seller_arr[i];

	delete[]m_seller_arr;
}
// ---------------------------------- setters ------------------------------------------

bool System::setName(const char* name)
{
	delete[] m_name;
	m_name = strdup(name);

	return true;
}
bool System::setSellersPhySize(int s_physize)
{
	m_sellers_phy_size = s_physize;
	return true;
}
bool System::setNumOfSellers(int num_of_sellers)
{
	m_num_of_sellers = num_of_sellers;
	return true;
}
bool System::setBuyersPhySize(int b_physize)
{
	m_buyers_phy_size = b_physize;
	return true;

}
bool System::setNumOfBuyers(int num_of_buyers)
{
	m_num_of_buyers = num_of_buyers;
	return true;

}

// ---------------------------------- maintanance functions ------------------------------------

const int System::isBuyerExist(const char* buyer_username)const
{//the func returns the index of a specific buyer according to his username or -1 if didn't exist
	for (int i = 0; i < m_num_of_buyers; i++)
	{
		if (strcmp(m_buyer_arr[i]->getUsername(), buyer_username) == 0)
			return i;
	}
	return NOT_EXIST;
}

void System::buyersRealloc()
{ // Extend the physic size of the buyers array
	m_buyers_phy_size *= 2;

	Buyer** temp = new Buyer*[m_buyers_phy_size];

	for (int i = 0; i < m_num_of_buyers; i++)
	{
		temp[i] = m_buyer_arr[i];
	}
	delete[] m_buyer_arr;

	m_buyer_arr = temp;
}

const int System::isSellerExist(const char* seller_username)const
{//the func returns the index of a specific seller according to his username or -1 if didn't exist
	for (int i = 0; i < m_num_of_sellers; i++)
	{
		if (strcmp(m_seller_arr[i]->getUsername(), seller_username) == 0)
			return i;
	}
	return NOT_EXIST;
}

void System::sellersRealloc()
{// Extend the physic size of the sellers array
	m_sellers_phy_size *= 2;

	Seller** temp = new Seller*[m_sellers_phy_size];

	for (int i = 0; i < m_num_of_sellers; i++)
	{
		temp[i] = m_seller_arr[i];
	}
	delete[] m_seller_arr;

	m_seller_arr = temp;
}


// ---------------------------------- MENU functions ------------------------------------


/************************************************************ 1 ********************************************************/

bool System::addToBuyerArr(Buyer* new_buyer)
{ // Add buyer to system buyers array
	if (isBuyerExist(new_buyer->getUsername())!=NOT_EXIST)
		return false; // username already exist

	if (m_num_of_buyers == m_buyers_phy_size)
		buyersRealloc();

	m_buyer_arr[m_num_of_buyers++] = new_buyer;

	return true; // new buyer entered
}

/************************************************************ 2 ********************************************************/

bool System::addToSellerArr(Seller* new_seller)
{// Add buyer to system sellers array
	if (isSellerExist(new_seller->getUsername()) != NOT_EXIST)
		return false; // username already exist

	if (m_num_of_sellers == m_sellers_phy_size)
		sellersRealloc();

	m_seller_arr[m_num_of_sellers++] = new_seller;

	return true; // new seller entered

}

/************************************************************ 3 ********************************************************/

bool System::addProductToSeller(Product* prod, const char* seller_username)
{// Add new product to exist seller 
	int seller_index = isSellerExist(seller_username);

	if (seller_index >= 0)
	{
		m_seller_arr[seller_index]->addToListItemsArr(prod);
		return true; // new product enterd to the seller
	}

	return false; //no such seller / invalid product
}

/******************************************************************  4  ***********************************************************/

bool System::addFeedbackToSeller(const char* buyer_username, const char* seller_username, FeedBack* feedback)
{// Add feedback to exist seller from exist buyer that allready buyed from him 
	int buyer_index = isBuyerExist(buyer_username);

	if (buyer_index == NOT_EXIST)
		return false; // no such buyer

	int seller_index = isSellerExist(seller_username);

	if (seller_index == NOT_EXIST)
		return false;// no such seller

	if (m_buyer_arr[buyer_index]->isOrderedFrom(m_seller_arr[seller_index]->getUsername())) //Check if the buyer allready buyed from this user
	{
		m_seller_arr[seller_index]->addToFeedArr(feedback);
		return true;
	}

	return false;
}
/*****************************************************************  5  *****************************************************/

bool System::addProductToBuyersCart(const char* prod_name, const char* buyer_username)
{// add product to exist buyer's cart 
	int buyer_index;

	buyer_index = isBuyerExist(buyer_username);
	if (buyer_index == NOT_EXIST)
		return false;

	int counter = 1;
	for (int j = 0; j < m_num_of_sellers; j++)
	{
		bool found = false;
		for (int k = 0; !found && k < m_seller_arr[j]->getNumOfListedItems(); k++)  // show all products with this name fron all the sellers
		{
			if (strcmp(m_seller_arr[j]->getListedItems()[k]->getName(), prod_name) == 0)
			{
				cout << counter++ << ") ";
				m_seller_arr[j]->getListedItems()[k]->showProductToBuyer();
				cout << endl;
				found = true;
			}

		}
	}
		char chosen_seller_username[MAX_LEN];
		int count = 0;
		int chosen_seller_index;
		do
		{

			if ((count++) > 0)     // Not the first try  
				cout << "No such seller's username."<< endl;

			cout << "please enter the desired seller's username that you want to buy from: ";
			cin.getline(chosen_seller_username, MAX_LEN);
			cout << endl;
			
			if (count == MAX_TRIES) // failed to enter seller name 3 time
			{
				cout << "Sorry, invalid inputs" << endl;
				return false;
			}
			chosen_seller_index = isSellerExist(chosen_seller_username);
		} while (chosen_seller_index == NOT_EXIST); //Lettin the user 3 times to enter thechosen seller from list

		Product* prod_to_cart = new Product(*(m_seller_arr[chosen_seller_index]->findProduct(prod_name))); //Using copy c'tor to put the product at the cart
		if (m_buyer_arr[buyer_index]->addToCart(prod_to_cart) == true) // Add the product to the buyer's cart
		{
			cout << "Product entered to cart seccessfully!" << endl;
			return true;
		}

	return false; // invalid input / buyer or product not exist
}


/*****************************************************************  6  *****************************************************/
bool System::newOrder(const char* buyer_username)
{// Make new order to buyer (choosing from his own cart)
	int buyer_index = isBuyerExist(buyer_username); //Check if the buyer exist 
	if (buyer_index == NOT_EXIST)
		return false;
	if (getBuyerArr()[buyer_index]->isEmptyCart())
	{
		cout << "\n\n\t No items in cart, You need to add an item to make an order.\n\n";
		return false;
	}
	
	int option;
	Order* new_order = new Order(m_buyer_arr[buyer_index]); // Make new order using c'tor
	do
	{ // The user check from list until he deciede to exit 
		m_buyer_arr[buyer_index]->showCart();

		cout << endl << "Please Choose the number of the product from the list:" << endl << "Enter -1 to exit from order." << endl;
		cin >> option;
		cin.ignore(1,'\n');

		if (option > 0 && option <= m_buyer_arr[buyer_index]->getNumberOfItems())
		{
			new_order->addToProdArr(m_buyer_arr[buyer_index]->getCart()[option - 1]); // Adding the chosen option to the order prod array (remove from cart, sum the prices)
			cout << "Item added to the Order successfully." << endl;
		}

		else if ((option != EXIT && option < 1) || option > m_buyer_arr[buyer_index]->getNumberOfItems()) // option validity check 
			cout << "Sorry, invalid option.";

	} while (option != EXIT && m_buyer_arr[buyer_index]->getNumberOfItems() != EMPTY); // While the user still have products to choose 

	m_buyer_arr[buyer_index]->addToCheckout(new_order); //Add the order to the buyer's orders array

	return true;
}
/*****************************************************************  7  *****************************************************/
bool System::payment(const char* buyer_username)
{//Pay on unpaid order
	int buyer_index = isBuyerExist(buyer_username);
	if (buyer_index == NOT_EXIST)
		return false;

	if (m_buyer_arr[buyer_index]->isEmptyCheckoutOrders())
	{
		cout << "\nCheckout cart is empty.\n";
		return false;
	}

	m_buyer_arr[buyer_index]->showCheckoutOrders(); // Show all of specific buyer orders 
	int option, count = 1;
	do
	{ //choose which order to pay
		cout << endl << "Please choose the number of the order to pay for: ";
		cin >> option;
		cin.ignore(1,'\n');

		if (option < 0 || option > m_buyer_arr[buyer_index]->getNumOfOrders())
			count++;

		if (count == MAX_TRIES) //faild to choose 3 times
		{
			cout << "Sorry, invalid inputs" << endl;
			return false;
		}

	} while (option<1 || option>m_buyer_arr[buyer_index]->getNumOfOrders()); // option validity check


	m_buyer_arr[buyer_index]->getOrders()[option - 1]->setPaid(true); // Sign the chosen order to "paid" lable
	cout << "Order paid successfully." << endl;
	return true;
}

/*****************************************************************  8  *****************************************************/

void System::printBuyers()const
{// Print all the buyers in the system 
	int i=0;
	for (i ; i < m_num_of_buyers; i++)
	{
		cout << i + 1 << ") ";
		m_buyer_arr[i]->showBuyer();
		cout << endl;
	}
	if (i == 0)
		cout << "No Buyers in the system"<< endl;
}

/*****************************************************************  9  *****************************************************/

void System::printSellers()const
{// Print all the sellers in the system 
	int i=0;
	for (i ; i < m_num_of_sellers; i++)
	{
		m_seller_arr[i]->showSeller();
		cout << endl;
	}
	if (i == 0)
		cout << "No Sellers in the system"<< endl;

}


/*****************************************************************  10  *****************************************************/

void System::printAllSpecificProduct(const char* name_to_find)const
{// Print all products with the chosen name that in the system 
	int counter = 1;
	for (int i = 0; i < m_num_of_sellers; i++) // Check every seller in the system
	{
		int num_of_prod = m_seller_arr[i]->getNumOfListedItems();  // How many product the seller have
		for (int j = 0; j < num_of_prod; j++)
		{
			if (strcmp(name_to_find, m_seller_arr[i]->getListedItems()[j]->getName()) == 0) // if choosen product name exist
			{
				cout << counter++ << ") ";
				m_seller_arr[i]->getListedItems()[j]->showProduct(); // Print 
				cout << endl;
			}
		}
	}
	if (!counter) 
		cout << "No such product in the system"<< endl;
}


/* ###  PRINT  ### */

void System::interactiveMenu()
{
	bool exit_flag = true;
	while (exit_flag)
	{
		int i = 1;
		cout << "----------------------------------------------------------Actions menu:----------------------------------------------------------" << endl;
		cout << (i++) << ") Add buyer" << endl;
		cout << (i++) << ") Add seller" << endl;
		cout << (i++) << ") Add product to seller" << endl;
		cout << (i++) << ") Add feedback" << endl;
		cout << (i++) << ") Add to cart" << endl;
		cout << (i++) << ") Order products" << endl;
		cout << (i++) << ") Payment" << endl;
		cout << (i++) << ") Show all buyers" << endl;
		cout << (i++) << ") Show all sellers" << endl;
		cout << (i++) << ") Show all products by name" << endl;
		cout << (i++) << ") Exit" << endl << endl;
		cout << "Please enter your action: ";
		int option;
		cin >> option;
		cin.ignore(1, '\n');

		switch (option)
		{
			char b_username[MAX_NAMES_LEN];
			char s_username[MAX_NAMES_LEN];
			char prod_name[MAX_NAMES_LEN];
			int b_index; // Latest update.

		case 1://add buyer

			if (!(addToBuyerArr(createBuyer())))
				cout << "Username already exist, please try again" << endl;
			break;

		case 2://add seller

			if (!(addToSellerArr(createSeller())))
				cout << "Username already exist, please try again" << endl;
			break;

		case 3: //add product to seller
			cout << "Enter the username of the seller: ";
			cin.getline(s_username, MAX_NAMES_LEN);
			Product* p;
			if (addProductToSeller(p = createProduct(s_username), s_username) == false)
			{
				cout << "No such seller username." << endl;
				delete p;
			}

			break;

		case 4: //add feedback to seller 
			FeedBack * f;
			cout << "Enter buyer's username: ";
			cin.getline(b_username, MAX_NAMES_LEN);

			cout << "Enter seller's username: ";
			cin.getline(s_username, MAX_NAMES_LEN);

			b_index = isBuyerExist(b_username);
			if (!getBuyerArr()[b_index]->isOrderedFrom(s_username)) //check if there was indeed an order made by THIS BUYER from THIS SERLLER.
				cout << "Invalid action, " << b_username << " didn't buy from " << s_username << endl;
			else
			{
				addFeedbackToSeller(b_username, s_username, f = createFeedback(b_username));
				cout << "Feedback added successfully." << endl;
			}

			break;

		case 5: //add to cart
			cout << "Enter the username of the buyer: ";
			cin.getline(b_username, MAX_NAMES_LEN);


			cout << "Enter the product name: ";
			cin.getline(prod_name, MAX_NAMES_LEN);

			if (addProductToBuyersCart(prod_name, b_username) == false)
			{
				cout << "Buyer or prod not exist in the system." << endl;
			}

			break;

		case 6:	//order
			cout << "Enter the username of the buyer:";
			cin.getline(b_username, MAX_NAMES_LEN);

			newOrder(b_username);

			break;

		case 7:	//payment
			cout << "Enter the username of the buyer:";
			cin.getline(b_username, MAX_NAMES_LEN);

			payment(b_username);

			break;

		case 8: //print all buyers
			cout << endl;
			printBuyers();

			break;
		case 9://print all sellers
			cout << endl;
			printSellers();

			break;
		case 10: // print all products from specific name  
			cout << "Enter the product name: ";
			cin.getline(prod_name, MAX_NAMES_LEN);

			cout << endl;
			printAllSpecificProduct(prod_name);

			break;

		case 11:
			cout << endl << "Thanks for using " << m_name << ", Bye Bye (:" << endl;
			exit_flag = false;
			break;
		default:
			cout << endl << "Ops... No such action" << endl << endl;
			break;
		}
	}
}