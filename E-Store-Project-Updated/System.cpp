#include "System.h"
#include <string>

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

bool System::isBuyerExist(const Buyer* buyer)const
{
	for (int i = 0; i < m_num_of_buyers; i++)
	{
		if (strcmp(m_buyer_arr[i].getUserName(), new_buyer->getUsername()) == 0)
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

bool System::addToBuyerArr(Buyer* new_buyer) // change in header
{
	if (isBuyerExist(new_buyer))
		return false; // username already exist

	if (m_num_of_buyers == m_buyers_phy_size)
		buyersRealloc();

	m_buyer_arr[m_num_of_buyers++] = new_buyer; // Correct place ?

	return true; // new buyer entered
}

/************************************************************ 2 ********************************************************/

bool System::isSellerExist(const Seller* seller)const
{
	for (int i = 0; i < m_num_of_sellers; i++)
	{
		if (strcmp(m_seller_arr[i].getUserName(), seller->getUsername()) == 0)
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


bool System::addToSellerArr(const Seller* new_seller)
{
	if (isSellerExist(new_seller))
		return false; // username already exist

	if (m_num_of_sellers == m_sellers_phy_size)
		sellersRealloc();

	m_seller_arr[m_num_of_sellers++] = new_seller; // Correct place ?

	return true; // new buyer entered

}

/************************************************************ 3 ********************************************************/

bool System::addProductToSeller(Product* prod, const char* username) //heaader change
{
	for (int i = 0; i < m_num_of_sellers; i++)
	{
		if (strcmp(m_seller_arr[i].getUserName(), username) == 0)
		{
			m_seller_arr[i].addProduct(prod); //Ben - TO DO at Seller&Buyer class func that add product to the prod_arr (you can write realloc same as mine) 
			return true;
		}
	}
	return false;
}

/*4*/

bool System::addFeedbackToSeller(const char* buyer_username, const char* seller_username, FeedBack* feedback)
{
	//check if buyer exist
	//check if seller exist

	if (flag) // both exist
	{

	}
}
/*****************************************************************  6  *****************************************************/
bool System::newOrder(const char* b_username, const char* s_username /*some more args*/)
{

}


/*8*/

void System::printBuyers()const
{
	for (int i = 0; i < m_num_of_buyers; i++)
		m_buyer_arr[i].printBuyer();
}

/*9*/

void System::printSellers()const
{
	for (int i = 0; i < m_num_of_sellers; i++)
		m_seller_arr[i].printSeller();
}


/*10*/

void System::printAllSpecificProduct(const char* name_to_find)const
{
	int counter;
	for (int i = 0; i < m_num_of_sellers; i++)
	{
		for (int j = 0; j < m_seller_arr[i].getNumOfProductd(); i++) //Ben - We need this attribute and func in seller
		{
			if (strcmp(name_to_find, m_seller_arr[i].productArr[j].getName()) == 0)
			{
				cout << counter++ << ") ";
				m_seller_arr[i].productArr[j].printProduct(); // Is there is private blocking here? 
				cout << endl;
			}
		}
	}
}