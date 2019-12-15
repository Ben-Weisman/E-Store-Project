#include "System.h"
#include <string>
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


/////////////////////////////////////////////////////////////menu functions/////////////////////////////////////////////////////////////


			/************************************************************ 1 ********************************************************/

bool System::isBuyerExist(const char* buyer_username)const
{
	for (int i = 0; i < m_num_of_buyers; ++i)
	{
		if (strcmp(m_buyer_arr[i]->getUsername(), buyer_username) == 0)
			return false;
	}
	return true;
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

bool System::isSellerExist(const char* seller_username)const
{
	for (int i = 0; i < m_num_of_sellers; ++i)
	{
		if (strcmp(m_seller_arr[i]->getUsername(), seller_username) == 0)
			return false;
	}
	return true;
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
	for (int i = 0; i < m_num_of_sellers; ++i)
	{
		if (strcmp(m_seller_arr[i]->getUsername(), seller_username) == 0)
		{
			m_seller_arr[i]->addToListItemsArr(prod); 
			return true;
		}
	}
	return false;
}

/******************************************************************  4  ***********************************************************/

bool System::addFeedbackToSeller(const char* buyer_username, const char* seller_username, FeedBack* feedback)
{
	if (isBuyerExist(buyer_username))
	{
		for (int i = 0; i < m_num_of_sellers; ++i) //until we found the seller (if exist) 
		{
			if (strcmp(m_seller_arr[i]->getUsername(),seller_username)==0)
			{
				m_seller_arr[i]->addToFeedArr(feedback);
				return true;
			}
		}
	}
	return false;
}

/*****************************************************************  5  *****************************************************/

//Note: we have problem here - (we dont want to make new prod at the main, just to choose one from the sellers)<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
bool System::addProductToBuyersCart(char* prod_name, const char* buyer_username)
{
	for (int i = 0; i < m_num_of_buyers; ++i)
	{
		if (strcmp(m_buyer_arr[i]->getUsername(), buyer_username) == 0)
		{
			int counter = 1;
				for (int j = 0; j < m_num_of_sellers; ++j)
				{ 
					for (int k = 0; k < m_seller_arr[j]->getNumOfListedItems(); ++k) //Ben: plaese add this method to seller class ****************************************************************************************8
					{
						if (strcmp(m_seller_arr[j]->getListedItems()[k], prod_name) == 0) // Nir: I think there is a const issue here
							cout << counter++ << ") ";
						cout << m_seller_arr[j]->getUsername(); //printing all the sellers that have choosen product
					}
					//STUCKED HERE - how can i save the right sellers place? <--------------------------------------------------------------------------------------------------------
					char choosen_seller_username[MAX_LEN];
					do
					{
						cout << "please enter the choosen seller's username: ";
						cin >> option;
					} while (option<1 || option>counter - 1);


							cout << "\nPlease Choose product:\n Enter -1 to exit from order.\n";
						cin >> option;

						if ((option != -1 && option < 1) || option > m_buyer_arr[i]->getNumberOfItems()) // ----> validity check to "option" - can couse the program to fly
							cout << "Sorry, invalid option.";

						m_buyer_arr[i]->addToCart(prod);
						return true;
					}
		}
	}
	return false;
}




/*****************************************************************  6  *****************************************************/
bool System::newOrder(const char* buyer_username)
{
	for (int i = 0; i < m_num_of_buyers; ++i)
	{
		if (strcmp(m_buyer_arr[i]->getUsername(), buyer_username) == 0)
		{
			int option;
			do
			{
				m_buyer_arr[i]->showCart();

				cout << "\nPlease Choose product:\n Enter -1 to exit from order.\n";
				cin >> option;

				if ((option != -1 && option < 1) || option > m_buyer_arr[i]->getNumberOfItems()) // ----> validity check to "option" - can couse the program to fly
					cout << "Sorry, invalid option.";
				//Order array?

			} while (option!=-1);


			return true;
		}
	}
}
/*****************************************************************  7  *****************************************************/
bool System::payment(const char* buyer_username)
{
	for (int i = 0; i < m_num_of_buyers; ++i)
	{
		if (strcmp(m_buyer_arr[i]->getUsername(), buyer_username) == 0)
		{
			m_buyer_arr[i]->showOrderList();      // Waiting for Ben function
			int option;
			do
			{
				cout << "Please Choose your option: ";
				cin >> option;
			} while (option<1 || option>m_buyer_arr[i]->getNumberOfOrders()); //Need this also

			Product** prod_to_buy = m_buyer_arr[i]->getOrders();

			for (int j = 0; j < m_buyer_arr[i]->getNumberOfOrders(); ++j)
				m_buyer_arr[i]->removeFromCart(prod_to_buy[j]);

				m_[option - 1]->setPaid(true);
			return true;
		}
	}
}


/*****************************************************************  8  *****************************************************/

void System::printBuyers()const
{
	for (int i = 0; i < m_num_of_buyers; ++i)
	{
		m_buyer_arr[i]->printBuyer();
		cout << endl;
	}
}

/*****************************************************************  9  *****************************************************/

void System::printSellers()const
{
	for (int i = 0; i < m_num_of_sellers; ++i)
	{
		m_seller_arr[i]->printSeller();
		cout << endl;
	}
}


/*****************************************************************  10  *****************************************************/

void System::printAllSpecificProduct(const char* name_to_find)const
{
	int counter;
	for (int i = 0; i < m_num_of_sellers; ++i)
	{
		for (int j = 0; j < m_seller_arr[i]->getNumOfProductd(); ++i) //Ben - We need this Method and func in seller
		{
			if (strcmp(name_to_find, m_seller_arr[i]->getListedItems()[j]->getName()) == 0)
			{
				cout << counter++ << ") ";
				m_seller_arr[i]->getListedItems()[j]->printProduct(); 
				cout << endl;
			}
		}
	}
}