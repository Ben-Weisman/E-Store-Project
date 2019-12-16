#include "System.h"
#include <string.h>
#include <iostream>
using namespace std;

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
////////////////////////////////////////setters////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool System::setName(const char* name)
{
	delete[] m_name;
	m_name = strdup(name);
}
bool System::setSellersPhySize(int s_physize)
{
	m_sellers_phy_size = s_physize;
}
bool System::setNumOfSellers(int num_of_sellers)
{
	m_num_of_sellers = num_of_sellers;
}
bool System::setBuyersPhySize(int b_physize)
{
	m_buyers_phy_size = b_physize;

}
bool System::setNumOfBuyers(int num_of_buyers)
{
	m_num_of_buyers = num_of_buyers;

}
/////////////////////////////////////////////getters////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* System::getName()const
{
	return m_name;
}


const Seller** System::getSellerArr()const
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


const Buyer** System::getBuyerArr()const
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
	for (int i = 0; i < m_num_of_buyers; ++i)
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
	if (isBuyerExist(new_buyer->getUsername()))
		return false; // username already exist

	if (m_num_of_buyers == m_buyers_phy_size)
		buyersRealloc();

	m_buyer_arr[m_num_of_buyers++] = new_buyer; 

	return true; // new buyer entered
}

/************************************************************ 2 ********************************************************/

const int System::isSellerExist(const char* seller_username)const
{
	for (int i = 0; i < m_num_of_sellers; ++i)
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
	if (isSellerExist(new_seller->getUsername()))
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

		if (seller_index>=0)
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
	//if (buyer_index = isBuyerExist(buyer_username) == NOT_EXIST || seller_index = isSellerExist(seller_username) == NOT_EXIST) ------> Show Aviv ????????????????????????????????/
	
	if (m_buyer_arr[buyer_index]->IsOrderedFrom(m_seller_arr[seller_index]->getUsername())) //Ben, please add this func
	{
		m_seller_arr[seller_index]->addToFeedArr(feedback);
		return true;
	}

	return false;
}
/*****************************************************************  5  *****************************************************/

bool System::addProductToBuyersCart(const char* prod_name, const char* buyer_username)
{
	int choosen_buyer_index;
	if (choosen_buyer_index = isSellerExist(buyer_username) >= 0)//check that work *********************************************************************
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
							m_seller_arr[j]->getListedItems()[k]->showProductToBuyer(); // Nir please add the func to Product *******************************************
							found = true;
						}
						
					}

					char choosen_seller_username[MAX_LEN];
					int count = 0;
					int choosen_seller_index; 
					do
					{
						
						if ((count++) > 0)     // Not the first try  
							cout << "No such seller's username.\n";

						cout << "please enter one of the seller's username: ";
						cin.getline(choosen_seller_username, MAX_LEN);
						cout << endl;

					} while (choosen_seller_index=isSellerExist(choosen_seller_username)>=0); // Until the user enter valid username - Nir Please change isExist func*****************************************8

					Product* prod_to_cart = new Product(m_seller_arr[choosen_seller_index]->getProduct(prod_name));
					m_buyer_arr[choosen_buyer_index]->addToCart(prod_to_cart); //Ben Please add the func ******************************************
					return true;
				}
		
	return false;
}


/*****************************************************************  6  *****************************************************/
bool System::newOrder(const char* buyer_username)
{
	int choosen_buyer_index;
	if (choosen_buyer_index = isSellerExist(buyer_username) >= 0)//check if that work *********************************************************************
		return false;

	int option;
	int total_price;
	Order* new_order=new Order(m_buyer_arr[choosen_buyer_index]); // FIX C'TOR **********************************************
			do
			{
				m_buyer_arr[choosen_buyer_index]->showCart();

				cout << "\nPlease Choose product:\n Enter -1 to exit from order.\n";
				cin >> option;

				if ((option != EXIT && option < 1) || option > m_buyer_arr[choosen_buyer_index]->getNumberOfItems()) // ----> validity check to "option" 
					cout << "Sorry, invalid option.";
				else
					new_order->addToProdArr(m_buyer_arr[choosen_buyer_index]->getCart()[option - 1]); //Nir, do this func*************************************

			} while (option!=EXIT);

			m_buyer_arr[choosen_buyer_index]->addToCheckout(new_order); // Ben, do this func ***************************************************************

			return true;
}
/*****************************************************************  7  *****************************************************/
bool System::payment(const char* buyer_username)
{
	int buyer_index;
	if (buyer_index = isBuyerExist(buyer_username) == NOT_EXIST)
		return false;

	m_buyer_arr[buyer_index]->showOrderList();      // Ben do this function **** Nir - Please change it to showCheckoutOrders
	int option;
	do
	{
		cout << "Please Choose your option: ";
		cin >> option;
	} while (option<1 || option>m_buyer_arr[buyer_index]->getNumOfOrders()); // Ben do this function *****************************************************************

	for (int i = 0; i < m_buyer_arr[buyer_index]->getOrders()[option-1]->getNumOfProducts(); ++i)
		m_buyer_arr[buyer_index]->getOrders()[option - 1]->setPaid(true);
	
	return true;
}

/*****************************************************************  8  *****************************************************/

void System::printBuyers()const
{
	int i;
	for (i = 0; i < m_num_of_buyers; ++i)
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
	for (i = 0; i < m_num_of_sellers; ++i)
	{
		m_seller_arr[i]->printSeller();
		cout << endl;
	}
	if (i == 0)
		cout << "No Sellers in the system\n";
	
}


/*****************************************************************  10  *****************************************************/

void System::printAllSpecificProduct(const char* name_to_find)const
{
	int counter;
	for (int i = 0; i < m_num_of_sellers; ++i)
	{
		for (int j = 0; j < m_seller_arr[i]->getNumOfProducts(); ++i) //Nir - Please change it to getNumOfListedItems
		{
			if (strcmp(name_to_find, m_seller_arr[i]->getListedItems()[j]->getName()) == 0)
			{
				cout << counter++ << ") ";
				m_seller_arr[i]->getListedItems()[j]->showProduct(); 
				cout << endl;
			}
		}
	}
	if(!counter)
		cout << "No such product in the system\n";
}