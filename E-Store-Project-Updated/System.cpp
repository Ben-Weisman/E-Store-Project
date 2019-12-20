#include "System.h"
#include "Order.h"
#include <string.h>
#include <iostream>

using namespace std;
#pragma warning(disable:4996) 

// --------------------- C'tor, D'tor ---------------------


System::System(const char* name = "eBen") //Default name
{
	cout << "\n########################################### IN SYSTEM C'TOR ###########################################\n";

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
	cout << "\n########################################### IN SYSTEM D'TOR ###########################################\n";
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
	if (buyer_index = isSellerExist(buyer_username) >= 0)
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
				found = true;
			}

		}

		char chosen_seller_username[MAX_LEN];
		int count = 0;
		int chosen_seller_index;
		do
		{

			if ((count++) > 0)     // Not the first try  
				cout << "No such seller's username.\n";

			cout << "please enter one of the seller's username: ";
			cin.getline(chosen_seller_username, MAX_LEN);
			cout << endl;

		} while (chosen_seller_index = isSellerExist(chosen_seller_username) != NOT_EXIST); //Check the valid seller username entered

		Product* prod_to_cart = new Product(*(m_seller_arr[chosen_seller_index]->findProduct(prod_name))); //Using copy c'tor to put the product at the cart
		m_buyer_arr[buyer_index]->addToCart(prod_to_cart); // Add the product to the buyer's caart
		return true;
	}

	return false; // invalid input / buyer or product not exist
}


/*****************************************************************  6  *****************************************************/
bool System::newOrder(const char* buyer_username)
{// Make new order to buyer (choosing from his own cart)
	int buyer_index = isSellerExist(buyer_username); //Check if the buyer exist 
	if (buyer_index >= 0)
		return false;

	int option;
	Order* new_order = new Order(m_buyer_arr[buyer_index]); // Make new order using c'tor
	do
	{ // The user check from list until he deciede to exit 
		m_buyer_arr[buyer_index]->showCart();

		cout << "\nPlease Choose product:\n Enter -1 to exit from order.\n";
		cin >> option;

		if ((option != EXIT && option < 1) || option > m_buyer_arr[buyer_index]->getNumberOfItems()) // option validity check 
			cout << "Sorry, invalid option.";
		else
			new_order->addToProdArr(m_buyer_arr[buyer_index]->getCart()[option - 1]); // Adding the chosen option to the order prod array (remove from cart, sum the prices)

	} while (option != EXIT);

	m_buyer_arr[buyer_index]->addToCheckout(new_order); //Add the order to the buyer's orders array

	return true;
}
/*****************************************************************  7  *****************************************************/
bool System::payment(const char* buyer_username)
{//Pay on unpaid order
	int buyer_index;
	if (buyer_index = isBuyerExist(buyer_username) == NOT_EXIST)
		return false;

	m_buyer_arr[buyer_index]->showCheckoutOrders(); // Show all of specific buyer orders 
	int option;
	do
	{ //choose which order to pay
		cout << "Please Choose your option: ";
		cin >> option;
	} while (option<1 || option>m_buyer_arr[buyer_index]->getNumOfOrders()); // option validity check


	m_buyer_arr[buyer_index]->getOrders()[option - 1]->setPaid(true); // Sign the chosen order to "paid" lable

	return true;
}

/*****************************************************************  8  *****************************************************/

void System::printBuyers()const
{// Print all the buyers in the system 
	int i;
	for (i = 0; i < m_num_of_buyers; i++)
	{
		m_buyer_arr[i]->showBuyer();
		cout << endl;
	}
	if (i == 0)
		cout << "No Buyers in the system\n";
}

/*****************************************************************  9  *****************************************************/

void System::printSellers()const
{// Print all the sellers in the system 
	int i;
	for (i = 0; i < m_num_of_sellers; i++)
	{
		m_seller_arr[i]->showSeller();
		cout << endl;
	}
	if (i == 0)
		cout << "No Sellers in the system\n";

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
		cout << "No such product in the system\n";
}