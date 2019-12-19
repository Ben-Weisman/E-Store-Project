#include "System.h"
#include "Order.h"
#include <string.h>
#include <iostream>

using namespace std;
#pragma warning(disable:4996) 

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
////////////////////////////////////////setters////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
/////////////////////////////////////////////getters////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* System::getName()const
{
	return m_name;
}


Seller** System::getSellerArr()const
{
	return m_seller_arr;
}
int System::getSellersPhySize()const
{
	return m_sellers_phy_size;
}
int System::getNumOfSellers()const
{
	return m_num_of_sellers;
}


Buyer** System::getBuyerArr()const
{
	return m_buyer_arr;
}
int System::getBuyersPhySize()const
{
	return m_buyers_phy_size;
}
int System::getNumOfBuyers()const
{
	return m_num_of_buyers;
}


/////////////////////////////////////////////////////////////  MENU functions  /////////////////////////////////////////////////////////////


			/************************************************************ 1 ********************************************************/

const int System::isBuyerExist(const char* buyer_username)const
{
	for (int i = 0; i < m_num_of_buyers; i++)
	{
		if (strcmp(m_buyer_arr[i]->getUsername(), buyer_username) == 0)
			return i;
	}
	return NOT_EXIST;
}

void System::buyersRealloc()
{
	m_buyers_phy_size *= 2;

	Buyer** temp = new Buyer*[m_buyers_phy_size];

	for (int i = 0; i < m_num_of_buyers; i++)
	{
		temp[i] = m_buyer_arr[i];
	}
	delete[] m_buyer_arr;

	m_buyer_arr = temp;
}

bool System::addToBuyerArr(Buyer* new_buyer)
{
	if (isBuyerExist(new_buyer->getUsername())!=NOT_EXIST)
		return false; // username already exist

	if (m_num_of_buyers == m_buyers_phy_size)
		buyersRealloc();

	m_buyer_arr[m_num_of_buyers++] = new_buyer;

	return true; // new buyer entered
}

/************************************************************ 2 ********************************************************/

const int System::isSellerExist(const char* seller_username)const
{
	for (int i = 0; i < m_num_of_sellers; i++)
	{
		if (strcmp(m_seller_arr[i]->getUsername(), seller_username) == 0)
			return i;
	}
	return NOT_EXIST;
}

void System::sellersRealloc()
{
	m_sellers_phy_size *= 2;

	Seller** temp = new Seller*[m_sellers_phy_size];

	for (int i = 0; i < m_num_of_sellers; i++)
	{
		temp[i] = m_seller_arr[i];
	}
	delete[] m_seller_arr;

	m_seller_arr = temp;
}


bool System::addToSellerArr(Seller* new_seller)
{
	if (isSellerExist(new_seller->getUsername()) != NOT_EXIST)
		return false; // username already exist

	if (m_num_of_sellers == m_sellers_phy_size)
		sellersRealloc();

	m_seller_arr[m_num_of_sellers++] = new_seller;

	return true; // new seller entered

}

/************************************************************ 3 ********************************************************/

bool System::addProductToSeller(Product* prod, const char* seller_username)
{
	int seller_index = isSellerExist(seller_username);

	if (seller_index >= 0)
	{
		m_seller_arr[seller_index]->addToListItemsArr(prod);
		return true;
	}

	return false;
}

/******************************************************************  4  ***********************************************************/

bool System::addFeedbackToSeller(const char* buyer_username, const char* seller_username, FeedBack* feedback)
{
	int buyer_index = isBuyerExist(buyer_username);
	if (buyer_index == NOT_EXIST)
		return false;
	int seller_index = isSellerExist(seller_username);
	if (seller_index == NOT_EXIST)
		return false;

	if (m_buyer_arr[buyer_index]->isOrderedFrom(m_seller_arr[seller_index]->getUsername())) //Check if the buyer allready buyed from this user
	{
		m_seller_arr[seller_index]->addToFeedArr(feedback);
		return true;
	}

	return false;
}
/*****************************************************************  5  *****************************************************/

bool System::addProductToBuyersCart(const char* prod_name, const char* buyer_username)
{
	int buyer_index;
	if (buyer_index = isSellerExist(buyer_username) >= 0)//check that work *********************************************************************
		return false;

	int counter = 1;
	for (int j = 0; j < m_num_of_sellers; ++j)
	{
		bool found = false;
		for (int k = 0; !found && k < m_seller_arr[j]->getNumOfListedItems(); ++k) // Nir: Ben, plaese add this method to seller class ****************************************************************************************8
		{
			if (strcmp(m_seller_arr[j]->getListedItems()[k]->getName(), prod_name) == 0) // Mabye we can improve the comlexity
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

		} while (chosen_seller_index = isSellerExist(chosen_seller_username) >= 0); 

		Product* prod_to_cart = new Product(*(m_seller_arr[chosen_seller_index]->findProduct(prod_name))); //using copy c'tor
		m_buyer_arr[buyer_index]->addToCart(prod_to_cart);
		return true;
	}

	return false;
}


/*****************************************************************  6  *****************************************************/
bool System::newOrder(const char* buyer_username)
{
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

	m_buyer_arr[buyer_index]->addToCheckout(new_order);

	return true;
}
/*****************************************************************  7  *****************************************************/
bool System::payment(const char* buyer_username)
{
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
{
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
{
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
{
	int counter = 1;
	for (int i = 0; i < m_num_of_sellers; i++)
	{
		int num_of_prod = m_seller_arr[i]->getNumOfListedItems();
		for (int j = 0; j < num_of_prod; j++)
		{
			if (strcmp(name_to_find, m_seller_arr[i]->getListedItems()[j]->getName()) == 0)
			{
				cout << counter++ << ") ";
				m_seller_arr[i]->getListedItems()[j]->showProduct();
				cout << endl;
			}
		}
	}
	if (!counter)
		cout << "No such product in the system\n";
}