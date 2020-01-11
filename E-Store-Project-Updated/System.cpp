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

	m_user_arr; // Users array
	int m_users_phy_size; // Users array physic size
	int m_num_of_users;
	
	setUsersPhySize(1);
	setNumOfUsers(0);
	m_user_arr = new User*[m_users_phy_size];
}

System::System(const System&s)
{
	*this = s; //using system = operator
}

System::~System()// d'tor
{
	delete[] m_name; //free name

	// free users arr: 

	for (int i = 0; i < m_num_of_users; i++)
		delete m_user_arr[i];

	delete[]m_user_arr;

	
}

// ---------------------------------- operators ------------------------------------------


const System& System::operator=(const System& s)
{

	if (this != &s)
	{
		setName(s.m_name);
		setNumOfUsers(s.m_num_of_users);
		setUsersPhySize(s.m_users_phy_size);
		
		for (int i = 0; i < m_num_of_users; i++)
			*(m_user_arr + i) = *(s.m_user_arr + i);
	}
	return *this;
}

bool System::operator+=(Buyer* new_buyer)// Add buyer to system buyers array
{
	if (isUserExist(new_buyer->getUsername()) != NOT_EXIST)
		return false; // username already exist

	if (m_num_of_users == m_users_phy_size)
		usersRealloc();

	m_user_arr[m_num_of_users++] = new_buyer;

	return true; // new buyer entered
}

bool System::operator+=(Seller* new_seller)
{// Add seller to sellers arr using += operator.
	if (isUserExist(new_seller->getUsername()) != NOT_EXIST)
		return false;

	if (m_num_of_users == m_users_phy_size)
		usersRealloc();

	m_user_arr[m_num_of_users++] = new_seller;

	return true; // new seller entered
}

bool System::operator+=(Buyer_Seller* new_buyer_seller)
{// Add seller to sellers arr using += operator.
	if (isUserExist(new_buyer_seller->getUsername()) != NOT_EXIST)
		return false;

	if (m_num_of_users == m_users_phy_size)
		usersRealloc();

	m_user_arr[m_num_of_users++] = new_buyer_seller;

	return true; // new buyer_seller entered
}

// ---------------------------------- setters ------------------------------------------

bool System::setName(const char* name)
{
	delete[] m_name;
	m_name = strdup(name);

	return true;
}

bool System::setUsersPhySize(int u_physize)
{
	m_users_phy_size = u_physize;
	return true;

}
bool System::setNumOfUsers(int num_of_users)
{
	m_num_of_users = num_of_users;
	return true;

}

// ---------------------------------- maintanance functions ------------------------------------

const int System::isUserExist(const char* username)const
{//the func returns the index of a specific buyer according to his username or -1 if didn't exist
	for (int i = 0; i < m_num_of_users; i++)
	{
		if (strcmp(m_user_arr[i]->getUsername(), username) == 0)
			return i;
	}
	return NOT_EXIST;
}

void System::usersRealloc()
{ // Extend the physic size of the buyers array
	m_users_phy_size *= 2;

	User** temp = new User*[m_users_phy_size];

	for (int i = 0; i < m_num_of_users; i++)
	{
		temp[i] = m_user_arr[i];
	}
	delete[] m_user_arr;

	m_user_arr = temp;
}


// ---------------------------------- MENU functions ------------------------------------


/************************************************************ 1 ********************************************************/

// Using System += Operator (with Buyer)

/************************************************************ 2 ********************************************************/

// Using System += Operator (with Seller)

/************************************************************ 3 ********************************************************/

// Using System += Operator (with Buyer_Seller)

// ## we need to discuss about the options here (Do we want to approve trasictions from seller/buyer to buyer_seller? )

/************************************************************ 4 ********************************************************/


bool System::addProductToSeller(Product* prod, const char* seller_username)
{// Add new product to exist seller 
	int seller_index = isUserExist(seller_username);
	if (seller_index == NOT_EXIST)
		return false;//no such user

	// Polymorphistic check if this is Seller/BuyerSeller:
	Seller* tmp1 = dynamic_cast<Seller*>(m_user_arr[seller_index]);
	Buyer_Seller* tmp2 = dynamic_cast<Buyer_Seller*>(m_user_arr[seller_index]);
	if (tmp1 || tmp2)
	{ // If the right type
		m_user_arr[seller_index]->addToListItemsArr(prod); 
		return true; // new product enterd to the seller
	}

	return false;  // no such seller OR invalid product
}

/******************************************************************  5  ***********************************************************/

bool System::addFeedbackToSeller(const char* buyer_username, const char* seller_username, FeedBack* feedback)
{// Add feedback to exist seller from exist buyer that allready buyed from him 
	int buyer_index = isUserExist(buyer_username);
	if (buyer_index == NOT_EXIST )
		return false; // no such user

	// Polymorphistic check if this is Buyer/BuyerSeller:
	Buyer* tmp1 = dynamic_cast<Buyer*>(m_user_arr[buyer_index]);
	Buyer_Seller* tmp2 = dynamic_cast<Buyer_Seller*>(m_user_arr[buyer_index]);
	if (!tmp1&&!tmp2)
		return false; // no such buyer

	int seller_index = isUserExist(seller_username);
	if (seller_index == NOT_EXIST)
		return false;// no such user

	// Polymorphistic check if this is Seller/BuyerSeller && 
	Seller* tmp3 = dynamic_cast<Seller*>(m_user_arr[seller_index]);
	Buyer_Seller* tmp4 = dynamic_cast<Buyer_Seller*>(m_user_arr[seller_index]);
	if (!tmp3 && !tmp4)
		return false;// no such seller

	if (buyer_index == seller_index)
		return false;// Buyer_Seller can't feedback himself

	if (m_user_arr[buyer_index]->isOrderedFrom(m_user_arr[seller_index]->getUsername())) //Check if the buyer allready buyed from this user
	{
		m_user_arr[seller_index]->addToFeedArr(feedback);
		return true;
	}

	return false;
}
/*****************************************************************  6  *****************************************************/

bool System::addProductToBuyersCart(const char* prod_name, const char* buyer_username)
{// add product to exist buyer's cart 
	int buyer_index = isUserExist(buyer_username);
	if (buyer_index == NOT_EXIST)
		return false;// no such user

	// Polymorphistic check if this is Buyer/BuyerSeller:
	Buyer* tmp1 = dynamic_cast<Buyer*>(m_user_arr[buyer_index]);
	Buyer_Seller* tmp2 = dynamic_cast<Buyer_Seller*>(m_user_arr[buyer_index]);
	if (!tmp1 && !tmp2)
		return false; //no such buyer

	int counter = 1;
	for (int j = 0; j < m_num_of_users; j++)
	{
		bool found = false;
		for (int k = 0; !found && k < m_user_arr[j]->getNumOfListedItems(); k++)  // show all products with this name fron all the sellers
		{
			if (strcmp(m_user_arr[j]->getListedItems()[k]->getName(), prod_name) == 0)
			{
				cout << counter++ << ") ";
				m_user_arr[j]->getListedItems()[k]->showProductToBuyer();
				cout << endl;
				found = true;
			}

		}
	}
		char chosen_seller_username[MAX_LEN];
		int count = 0;
		int chosen_seller_index;
		bool type_flag = true;
		do
		{

			if ((count++) > 0)   // Not the first try  
				cout << "No such seller's username."<< endl;

			cout << "please enter the desired seller's username that you want to buy from: ";
			cin.getline(chosen_seller_username, MAX_LEN);
			cout << endl;
			
			if (count == MAX_TRIES) // failed to enter seller name 3 time
			{
				cout << "Sorry, invalid inputs" << endl;
				return false;
			}

			chosen_seller_index = isUserExist(chosen_seller_username);

			Seller* tmp3 = dynamic_cast<Seller*>(m_user_arr[chosen_seller_index]);
			Buyer_Seller* tmp4 = dynamic_cast<Buyer_Seller*>(m_user_arr[chosen_seller_index]);
			type_flag = (!tmp3 && !tmp4);  // ### CHECK that line! 
			
		} while (chosen_seller_index == NOT_EXIST && type_flag); //Lettin the user 3 times to enter the chosen seller from list

		Product* prod_to_cart = new Product(*(m_user_arr[chosen_seller_index]->findProduct(prod_name))); //Using copy c'tor to put the product at the cart
		if (m_user_arr[buyer_index]->addToCart(prod_to_cart) == true) // Add the product to the buyer's cart
		{
			cout << "Product entered to cart seccessfully!" << endl;
			return true;
		}

	return false; // invalid input / buyer or product not exist
}


/*****************************************************************  7  *****************************************************/
bool System::newOrder(const char* buyer_username)
{// Make new order to buyer (choosing from his own cart)
	int buyer_index = isUserExist(buyer_username); //Check if the buyer exist 
	if (buyer_index == NOT_EXIST)
		return false; // no such user
	//## Polymorphistic check if this is Buyer/BuyerSeller:
	Buyer* tmp1 = dynamic_cast<Buyer*>(m_user_arr[buyer_index]);
	Buyer_Seller* tmp2 = dynamic_cast<Buyer_Seller*>(m_user_arr[buyer_index]);
	if (!tmp1 && !tmp2)
		return false; //no such buyer


	if (getUsersArr()[buyer_index]->isEmptyCart())
	{
		cout << "\n\n\t No items in cart, You need to add an item to make an order.\n\n";
		return false;
	}
	
	int option;
	Order* new_order = new Order(m_user_arr[buyer_index]); // Make new order using c'tor
	do
	{ // The user check from list until he deciede to exit 
		m_user_arr[buyer_index]->showCart();

		cout << endl << "Please Choose the number of the product from the list:" << endl << "Enter -1 to exit from order." << endl;
		cin >> option;
		cin.ignore(1,'\n');

		if (option > 0 && option <= m_user_arr[buyer_index]->getNumberOfItems())
		{
			new_order->addToProdArr(m_user_arr[buyer_index]->getCart()[option - 1]); // Adding the chosen option to the order prod array (remove from cart, sum the prices)
			cout << "Item added to the Order successfully." << endl;
		}

		else if ((option != EXIT && option < 1) || option > m_user_arr[buyer_index]->getNumberOfItems()) // option validity check 
			cout << "Sorry, invalid option.";

	} while (option != EXIT && m_user_arr[buyer_index]->getNumberOfItems() != EMPTY); // While the user still have products to choose 

	m_user_arr[buyer_index]->addToCheckout(new_order); //Add the order to the buyer's orders array

	return true;
}

/*****************************************************************  8  *****************************************************/
bool System::payment(const char* buyer_username)
{//Pay on unpaid order
	int buyer_index = isUserExist(buyer_username);
	if (buyer_index == NOT_EXIST)
		return false;
	//## Polymorphistic check if this is Buyer/BuyerSeller


	if (m_user_arr[buyer_index]->isEmptyCheckoutOrders())
	{
		cout << "\nCheckout cart is empty.\n";
		return false;
	}

	m_user_arr[buyer_index]->showCheckoutOrders(); // Show all of specific buyer orders 
	int option, count = 1;
	do
	{ //choose which order to pay
		cout << endl << "Please choose the number of the order to pay for: ";
		cin >> option;
		cin.ignore(1,'\n');

		if (option < 0 || option > m_user_arr[buyer_index]->getNumOfOrders())
			count++;

		if (count == MAX_TRIES) //faild to choose 3 times
		{
			cout << "Sorry, invalid inputs" << endl;
			return false;
		}

	} while (option<1 || option>m_user_arr[buyer_index]->getNumOfOrders()); // option validity check


	m_user_arr[buyer_index]->getOrders()[option - 1]->setPaid(true); // Sign the chosen order to "paid" lable
	cout << "Order paid successfully." << endl;
	return true;
}

/*****************************************************************  9  *****************************************************/

void System::printBuyers()const
{// Print all the buyers in the system 
	int i=0;
	for (i ; i < m_num_of_users; i++)
	{
		cout << i + 1 << ") ";

		// Some buyer/buyerseller POLY check and print according to that (include the buyersellers)
		//m_buyer_arr[i]->showBuyer();
		cout << m_user_arr[i] << endl; // Dynamic cast?
	}
	if (i == 0)
		cout << "No Buyers in the system"<< endl;
}

/*****************************************************************  10  *****************************************************/

void System::printSellers()const
{// Print all the sellers in the system 
	int i=0;
	for (i ; i < m_num_of_users; i++)
	{
		cout << i + 1 << ") ";

		// Some seller/buyerseller POLY check and print according to that (include the buyersellers)
		//m_seller_arr[i]->showSeller();
		cout << m_user_arr[i] << endl; // Dynamic cast?
	}
	if (i == 0)
		cout << "No Sellers in the system"<< endl;

}


/*****************************************************************  11  *****************************************************/
void System::printBuyerSellers()const
{// Print all the buyersellers in the system 
	int i = 0;
	for (i; i < m_num_of_users; i++)
	{
		cout << i + 1 << ") ";

		// ##Some buyerseller POLY check and print according to that 
		//m_seller_arr[i]->showSeller();
		cout << m_user_arr[i] << endl; // Dynamic cast?
	}
	if (i == 0)
		cout << "No Sellers in the system" << endl;

}

/*****************************************************************  12  *****************************************************/


void System::printAllSpecificProduct(const char* name_to_find)const
{// Print all products with the chosen name that in the system 
	int counter = 1;
	for (int i = 0; i < m_num_of_users; i++) // Check every seller in the system
	{
		//##Some Buyer / BuyerSeller POLY check
		int num_of_prod = m_seller_arr[i]->getNumOfListedItems();  // How many product the seller have
		for (int j = 0; j < num_of_prod; j++)
		{
			if (strcmp(name_to_find, m_seller_arr[i]->getListedItems()[j]->getName()) == 0) // if choosen product name exist
			{
				cout << counter++ << ") ";
				//m_seller_arr[i]->getListedItems()[j]->showProduct(); // Nir: # Replaced by operator <<
				cout << m_seller_arr[i]->getListedItems()[j];  // Nir: # using operator <<
				cout << endl;
			}
		}
	}
	if (!counter) 
		cout << "No such product in the system"<< endl;
}


/* ----- PRINT ------ */

void System::interactiveMenu()
{
	bool exit_flag = true;
	while (exit_flag)
	{
		int i = 1;
		cout << "----------------------------------------------------------Actions menu:----------------------------------------------------------" << endl;
		cout << (i++) << ") Add buyer" << endl; //1
		cout << (i++) << ") Add seller" << endl; //2
		cout << (i++) << ") Add buyer-seller" << endl; //3
		cout << (i++) << ") Add product to seller" << endl; //4
		cout << (i++) << ") Add feedback" << endl; //5
		cout << (i++) << ") Add to cart" << endl; //6 
		cout << (i++) << ") Order products" << endl; //7
		cout << (i++) << ") Payment" << endl; //8
		cout << (i++) << ") Show all buyers" << endl; //9
		cout << (i++) << ") Show all sellers" << endl; //10
		cout << (i++) << ") Show all products by name" << endl; //11
		cout << (i++) << ") Compare between tow carts" << endl << endl; //12
		cout << (i++) << ") Exit" << endl << endl; //13
		cout << "Please enter your action: "; //14
		int option;
		cin >> option;
		cin.ignore(1, '\n');

		switch (option)
		{
			char b_username[MAX_NAMES_LEN];
			char s_username[MAX_NAMES_LEN];
			char prod_name[MAX_NAMES_LEN];
			int b_index; // Latest update.

		case 1://add buyer (Check for += operator)
			
			//if (!(addToBuyerArr(createBuyer())))
			Buyer* new_buyer(createBuyer());
			if(!((*this)+=new_buyer)) //using system's += operator ( check if the user already exist )
				cout << "Username already exist, please try again" << endl;
			break;

		case 2://add seller (Check for += operator)

			Seller* new_seller(createSeller());
			if (!((*this) += new_seller)) //using system's += operator ( check if the user already exist )
				cout << "Username already exist, please try again" << endl;
			break;

		case 3://add buyer-seller

			Buyer_Seller* new_bs(createBuyerSeller()); // # Nir: I think we should change the ctor according to that
			if (/* check if the user already exist*/ ) 
				cout << "Username already exist, please try again" << endl;
               //## Impliment 
			break;

		case 4: //add product to seller
			cout << "Enter the username of the seller: ";
			cin.getline(s_username, MAX_NAMES_LEN);
			Product* p;
			if (addProductToSeller(p = createProduct(s_username), s_username) == false)
			{
				cout << "No such seller username." << endl;
				delete p;
			}

			break;

		case 5: //add feedback to seller 
			FeedBack * f;
			cout << "Enter buyer's username: ";
			cin.getline(b_username, MAX_NAMES_LEN);

			cout << "Enter seller's username: ";
			cin.getline(s_username, MAX_NAMES_LEN);

			b_index = isUserExist(b_username);
			//## POLY check
			if (!getUsersArr()[b_index]->isOrderedFrom(s_username)) //check if there was indeed an order made by THIS BUYER from THIS SERLLER.
				cout << "Invalid action, " << b_username << " didn't buy from " << s_username << endl;
			else
			{
				addFeedbackToSeller(b_username, s_username, f = createFeedback(b_username));
				cout << "Feedback added successfully." << endl;
			}

			break;

		case 6: //add to cart
			cout << "Enter the username of the buyer: ";
			cin.getline(b_username, MAX_NAMES_LEN);


			cout << "Enter the product name: ";
			cin.getline(prod_name, MAX_NAMES_LEN);

			if (addProductToBuyersCart(prod_name, b_username) == false)
			{
				cout << "Buyer or prod not exist in the system." << endl;
			}

			break;

		case 7:	//order
			cout << "Enter the username of the buyer:";
			cin.getline(b_username, MAX_NAMES_LEN);

			newOrder(b_username);

			break;

		case 8:	//payment
			cout << "Enter the username of the buyer:";
			cin.getline(b_username, MAX_NAMES_LEN);

			payment(b_username);

			break;

		case 9: //print all buyers
			cout << endl;
			printBuyers();

			break;
		case 10://print all sellers (Check for Buyer << operator)
			cout << endl;
			printSellers();

		case 11://print all sellers (Check for Seller << operator)
			cout << endl;
			printBuyerSellers();

			break;
		case 12: // print all products from specific name  (Check for Product << operator)
			cout << "Enter the product name: ";
			cin.getline(prod_name, MAX_NAMES_LEN);

			cout << endl;
			printAllSpecificProduct(prod_name);

			break;

		case 13: // "Which cart cheeper?" (Check for > operator)
			

		case 14: //
			cout << endl << "Thanks for using " << m_name << ", Bye Bye (:" << endl;
			exit_flag = false;
			break;

		default:
			cout << endl << "Ops... No such action" << endl << endl;
			break;
		}
	}
}