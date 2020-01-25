#include "System.h"
#include "Source.h"
#include "Order.h"
#include <iostream>

using namespace std;

// --------------------- C'tor, D'tor ---------------------


System::System(const string& file_name, const string& name = "eBen") //Default name
{
	loadUsers(file_name);
	setName(name);
}


System::System(const System&s)
{
	*this = s; //using system = operator
}

System::~System()// d'tor
{
	for (auto user_ptr : m_user_arr)
		delete user_ptr;
}

// ---------------------------------- operators ------------------------------------------


const System& System::operator=(const System& s)
{
	if (this != &s)
	{
		setName(s.m_name);
		
		m_user_arr.reserve(s.m_user_arr.size()); // allocate the place to users array
		for (int i = 0; i < s.m_user_arr.size(); i++)
		{
			m_user_arr[i] = s.m_user_arr[i]; // user = operator
		}
	}
	return *this;
}

bool System::operator+=(User* new_user) 
{// Add user to arr using += operator. 
	if (isUserExist(new_user->getUsername()) != NOT_EXIST)
		return false;

	m_user_arr.push_back(new_user);
	return true; // new buyer_seller entered
}


// ---------------------------------- setters ------------------------------------------

bool System::setName(const string& name)
{
	if (name.length() <= 1)
		return false; // system name should be more them 1 letter
	m_name = name;
	return true;
}


// ---------------------------------- maintanance functions ------------------------------------

const int System::isUserExist(const string& username)const
{//the func returns the index of a specific buyer according to his username or -1 if didn't exist
	int i = 0;
	for (auto& user_ptr : m_user_arr)
	{
		if (user_ptr->getUsername()==username)
			return i;

		i++;
	}
	return NOT_EXIST;
}

void System::saveUsers(const string& filename)
{
	ofstream out_file(filename, ios::trunc);

	out_file << m_user_arr.size() << " ";
	for (int i = 0; i < m_user_arr.size(); ++i)
	{
		// Polymorphistic check if this is Buyer/Seller/BuyerSeller:
		Buyer* tmp_b = dynamic_cast<Buyer*>(m_user_arr[i]); 
		Seller* tmp_s = dynamic_cast<Seller*>(m_user_arr[i]);

		if(tmp_b&&!tmp_s) //buyer
		out_file << BUYER << " ";
		else if (!tmp_b && tmp_s) // seller
			out_file << SELLER << " ";
		else // (tmp_b && tmp_s)
			out_file << BUYERSELLER << " ";

		out_file << *(m_user_arr[i]) << " ";
	}

	out_file.close();
}
//-----------------------------------------------------------------------------------------------//
void System::loadUsers(const string& filename) 
{
	ifstream in_file;
	int size;
	int type;

		in_file.open(filename, ios::in);
		in_file >> size;

		m_user_arr.reserve(size); //allocate the place 

		// @@ Shouldn't we return the new allocated object? @@@@ Why? we can do it on the object's array @@@ 
		for (int i = 0; i < size; ++i)
		{
			in_file >> type;
		
			if (type == BUYER)
				m_user_arr[i] = new Buyer(in_file);
			else if (type == SELLER)
				m_user_arr[i] = new Seller(in_file);
			else //(type == BUYERSELLER)
				m_user_arr[i] = new Buyer_Seller(in_file);

	    }

	in_file.close();
}




// ---------------------------------- MENU functions ------------------------------------


/************************************************************ 1 ********************************************************/

// Using System += Operator (with Buyer)

/************************************************************ 2 ********************************************************/

// Using System += Operator (with Seller)

/************************************************************ 3 ********************************************************/

// Using System += Operator (with Buyer_Seller)

/************************************************************ 4 ********************************************************/

bool System::addProductToSeller(Product* prod, const string& seller_username)
{// Add new product to exist seller 
	int seller_index = isUserExist(seller_username);
	if (seller_index == NOT_EXIST)
		return false;//no such user

	// Polymorphistic check if this is Seller/BuyerSeller:
	Seller* tmp_s = dynamic_cast<Seller*>(m_user_arr[seller_index]);
	if (tmp_s)
	{ // If the right type
		tmp_s->addToListItemsArr(prod);
		return true; // new product enterd to the seller
	}
	
	return false;  // no such seller OR invalid product
}

/******************************************************************  5  ***********************************************************/

bool System::addFeedbackToSeller(const string& buyer_username, const string& seller_username, FeedBack* feedback)
{// Add feedback to exist seller from exist buyer that allready buyed from him 
	int buyer_index = isUserExist(buyer_username);
	if (buyer_index == NOT_EXIST )
		return false; // no such user
	Buyer* tmp_b = dynamic_cast<Buyer*>(m_user_arr[buyer_index]); // Polymorphistic check if this is Buyer/BuyerSeller
	if (!tmp_b)
		return false; // no such buyer

	int seller_index = isUserExist(seller_username);
	if (seller_index == NOT_EXIST)
		return false;// no such user
	Seller* tmp_s = dynamic_cast<Seller*>(m_user_arr[seller_index]);// Polymorphistic check if this is Seller/BuyerSeller:
	if (!tmp_s)
		return false;// no such seller

	if (buyer_index == seller_index)
		return false;// Buyer_Seller can't feedback himself
	
		if (tmp_b->isOrderedFrom(tmp_s->getUsername()))
		{
			tmp_s->addToFeedArr(feedback);
			return true;
		}

	return false;
}
/*****************************************************************  6  *****************************************************/

bool System::addProductToBuyersCart(const string& prod_name, const string& buyer_username)
{// add product to exist buyer's cart 
	int buyer_index = isUserExist(buyer_username);
	if (buyer_index == NOT_EXIST)
		return false;// no such user

	Buyer* tmp_b = dynamic_cast<Buyer*>(m_user_arr[buyer_index]);// Polymorphistic check if this is Buyer/BuyerSeller:
	if (!tmp_b)
		return false; //no such buyer
	
	int counter = 0;
	Seller* tmp_s=nullptr;
	for (int j = 0; j < m_user_arr.size(); j++)
	{
		bool found = false;
		tmp_s = dynamic_cast<Seller*>(m_user_arr[j]);// Polymorphistic check if this is Seller/BuyerSeller:
		if (tmp_s)
		{
			for (int k = 0; !found && k < tmp_s->getNumOfListedItems(); k++)  // show all products with this name fron all the sellers
			{
				if (tmp_s->getListedItems()[k]->getName() == prod_name)
				{
					cout << ++counter << ") ";
					tmp_s->getListedItems()[k]->showProductToBuyer();
					cout << endl;
					found = true;
				}
			}
		}
	}

	if (counter == 0)   // No such product on the system 
		return false;

		string chosen_seller_username;
		int count = 0;
		int chosen_seller_index;
		do
		{

			if ((count++) > 0)   // Not the first try  
				cout << "Please try again."<< endl;

			cout << "Enter the desired seller's username that you want to buy from: ";
			getline(cin, chosen_seller_username);
			cout << endl;
			
			if (count == MAX_TRIES) // failed to enter seller name 3 time
			{
				cout << "Sorry, to many invalid inputs" << endl;
				return false;
			}

			chosen_seller_index = isUserExist(chosen_seller_username);
			if(chosen_seller_index != NOT_EXIST)
			tmp_s = dynamic_cast<Seller*>(m_user_arr[chosen_seller_index]);

			if (chosen_seller_index == buyer_index)
			{
				cout << "Can't buy from yourself !";
				chosen_seller_index = NOT_EXIST;
			}

		} while (chosen_seller_index == NOT_EXIST || !tmp_s); //Lettin the user 3 times to enter the chosen seller from list 
		//while choosen seller isnt exist or the he is not seller 
		 
		if (tmp_b&&tmp_s)
		{
			Product* prod_to_cart = new Product(*(tmp_s->findProduct(prod_name))); //Using copy c'tor to put the product at the cart
			if (tmp_b->addToCart(prod_to_cart) == true) // Add the product to the buyer's cart
			{
				cout << "Product entered to cart seccessfully!" << endl;
				return true;
			}
		}

	return false; // invalid input / buyer or product not exist
}

/*****************************************************************  7  *****************************************************/

bool System::newOrder(const string& buyer_username)
{// Make new order to buyer (choosing from his own cart)
	int buyer_index = isUserExist(buyer_username); //Check if the buyer exist 
	if (buyer_index == NOT_EXIST)
		return false; // no such user
	Buyer* tmp_b = dynamic_cast<Buyer*>(m_user_arr[buyer_index]);// Polymorphistic check if this is Buyer/BuyerSeller
	if (!tmp_b)
		return false; //no such buyer

	Order* new_order = nullptr;
	int option;

	if (tmp_b)
	{
		if (tmp_b->isEmptyCart())
		{
			cout << "\n\n\t No items in cart, You need to add an item to make an order.\n\n";
			return false;
		}
		new_order = new Order(tmp_b);// Make new order using c'tor
		
		do
		{ // The user check from list until he deciede to exit 
			tmp_b->showCart();

			cout << endl << "Please Choose the number of the product from the list:" << endl << "Enter -1 to exit from order." << endl;
			cin >> option;
			cin.ignore(1, '\n');

			if (option > 0 && option <= tmp_b->m_cart.getNumberOfItems())
			{
				new_order->addToProdArr(tmp_b->getCart()[option - 1]); // Adding the chosen option to the order prod array (remove from cart, sum the prices)
				cout << "Item added to the Order successfully." << endl;
			}

			else if ((option != EXIT && option < 1) || option > tmp_b->m_cart.getNumberOfItems()) // option validity check 
				cout << "Sorry, invalid option."<<endl;
		} while (option != EXIT && tmp_b->m_cart.getNumberOfItems() != EMPTY); // While the user still have products to choose 
	}

	if(tmp_b->m_cart.getNumberOfItems() == EMPTY)
		cout << "Your cart is empty."<<endl;
	
	if (tmp_b) //Buyer
		tmp_b->addToCheckout(new_order); //Add the order to the buyer's orders array
	if (new_order->getProductsArr().size() == 0) // Checking if the user entered this function but exited immediately.
	{
		delete tmp_b->m_checkout_orders.back(); /*  returns a DIRECT reference to the last element in the vector, then delete it.*/
		tmp_b->m_checkout_orders.pop_back(); /*  removing the last element (cell) from the vector + updating the size*/
	}
	return true;
}

/*****************************************************************  8  *****************************************************/
bool System::payment(const string& buyer_username)
{//Pay on unpaid order
	int buyer_index = isUserExist(buyer_username);
	if (buyer_index == NOT_EXIST)
		return false;//no such user

	Buyer* tmp_b = dynamic_cast<Buyer*>(m_user_arr[buyer_index]);
	if (!tmp_b)//Polymorphistic check if this is Buyer/BuyerSeller
		return false; //no such buyer

	if (tmp_b->isEmptyCheckoutOrders())
	{
		cout << "\nCheckout cart is empty.\n";
		return false;
	}

	tmp_b->showCheckoutOrders(); // Show all of specific buyer orders 
	int option, count = 1;
	do
	{ //choose which order to pay
		cout << endl << "Please choose the number of the order to pay for: ";
		cin >> option;
		cin.ignore(1,'\n');

		if (option < 0 || option > tmp_b->getNumOfOrders())
			count++;

		if (count == MAX_TRIES) //faild to choose 3 times
		{
			cout << "Sorry, invalid inputs" << endl;
			return false;
		}

	} while (option<1 || option>tmp_b->getNumOfOrders()); // option validity check


	tmp_b->getBuyerOrders()[option - 1]->setPaid(true); // Sign the chosen order to "paid" lable
	cout << "Order paid successfully." << endl;
	return true;
}

/*****************************************************************  9  *****************************************************/

void System::printBuyers()const
{// Print all the buyers in the system 
	int i=0, counter=1;
	for (i ; i < m_user_arr.size(); i++)
	{
		Buyer* tmp_b = dynamic_cast<Buyer*>(m_user_arr[i]);
		if (tmp_b) //Polymorphistic check if this is Buyer/BuyerSeller
		{
			cout << counter++ << ") ";
			cout << *tmp_b << endl; //buyer << operator
		}
		cout << endl;
	}
	if (i == 0)
		cout << "No Buyers in the system"<< endl;
}

/*****************************************************************  10  *****************************************************/

void System::printSellers()const
{// Print all the sellers in the system 
	int i=0, counter=1;
	for (i ; i < m_user_arr.size(); i++)
	{
		Seller* tmp_s = dynamic_cast<Seller*>(m_user_arr[i]); 
		if (tmp_s)//Polymorphistic check if this is Seller/BuyerSeller
		{
			cout << counter++ << ") ";
		    cout << *tmp_s << endl; //seller << operator
		}
		cout << endl;
	}
	if (i == 0)
		cout << "No Sellers in the system"<< endl;
}


/*****************************************************************  11  *****************************************************/
void System::printBuyerSellers()const
{// Print all the buyersellers in the system 
	int i = 0, counter=1;
	for (i; i < m_user_arr.size(); i++)
	{
		Buyer_Seller* tmp_bs = dynamic_cast<Buyer_Seller*>(m_user_arr[i]); 
		if (tmp_bs)//Polymorphistic check if this is BuyerSeller
		{
			cout << counter++ << ") ";
			cout << *tmp_bs << endl; //buyer_seller << operator
		}
		cout << endl;
	}
	if (i == 0)
		cout << "No Sellers in the system" << endl;

}

/*****************************************************************  12  *****************************************************/


void System::printAllSpecificProduct(const string& name_to_find)const
{// Print all products with the chosen name that in the system 
	int counter = 1;
	for (int i = 0; i < m_user_arr.size(); i++) // Check every seller in the system
	{
		int num_of_prod;
		Seller* tmp_s = dynamic_cast<Seller*> (m_user_arr[i]); 
		if (tmp_s) //Polymorphistic check if this is Seller/BuyerSeller
		{
			num_of_prod = tmp_s->getNumOfListedItems();  // How many product the seller have
			for (int j = 0; j < num_of_prod; j++)
			{
				if (name_to_find== tmp_s->getListedItems()[j]->getName()) // if choosen product name exist
				{
					cout << counter++ << ") ";
					cout << *(tmp_s->getListedItems()[j]);
					cout << endl;
				}
			}
		}
	}
	if (!counter) 
		cout << "No such product in the system"<< endl;
}

/*****************************************************************  13  *****************************************************/

void System::compareBuyersByCart(const string& username1, const string& username2)const
{// Compare tow buyers according to thier cart 
	int first_buyer_index = isUserExist(username1), second_buyer_index = isUserExist(username2);
	if (first_buyer_index == NOT_EXIST || second_buyer_index == NOT_EXIST)
	{
		cout << "At least one of the buyer not exist" << endl;
		return;//no such user
	}
		
	Buyer* tmp_b1 = dynamic_cast<Buyer*>(m_user_arr[first_buyer_index]), *tmp_b2 = dynamic_cast<Buyer*>(m_user_arr[second_buyer_index]);
	if (!tmp_b1 || !tmp_b2)//Polymorphistic check if this is Buyer/BuyerSeller
	{
		cout << "At least one of the buyer not exist" << endl;
		return; //at-least one buyer not exist
	}

	if (*tmp_b1 > *tmp_b2)
		cout << username1 << "'s cart total price is greater from " << username2 << "'s cart total price" << endl << endl;
	else if (*tmp_b2 > *tmp_b1)
		cout << username2 << "'s cart total price is greater from " << username1 << "'s cart total price" << endl << endl;
	else
		cout << username1 << "'s cart total price is equals to " << username2 << "'s cart total price" << endl << endl;;
}
/**********************************************************************************************************************/

                                                 /* ----- PRINT ------ */

void System::interactiveMenu()
{
	bool exit_flag = true;
	while (exit_flag)
	{
		int i = 1;
		cout << "----------------------------------------------------------Actions menu:----------------------------------------------------------" << endl;
		cout << (i++) << ") Add buyer" << endl; //1 -----> Use += operator
		cout << (i++) << ") Add seller" << endl; //2 -----> Use += operator
		cout << (i++) << ") Add buyer-seller" << endl; //3 -----> Use += operator
		cout << (i++) << ") Add product to seller" << endl; //4
		cout << (i++) << ") Add feedback" << endl; //5
		cout << (i++) << ") Add to cart" << endl; //6 
		cout << (i++) << ") Order products" << endl; //7
		cout << (i++) << ") Payment" << endl; //8
		cout << (i++) << ") Show all buyers" << endl; //9 -----> Use << operator
		cout << (i++) << ") Show all sellers" << endl; //10 -----> Use << operator
		cout << (i++) << ") Show all buyer-sellers" << endl; //11
		cout << (i++) << ") Show all products by name" << endl; //12 -----> Use << operator
		cout << (i++) << ") Compare between two carts" << endl << endl; //13 -----> Use > operator
		cout << (i++) << ") Exit" << endl << endl; //14
		cout << "Please enter your action: "; 
		int option;
		cin >> option;
		cin.ignore(1, '\n');

		//////////////For the switch cases:///////////////
		string b_username, b2_username, s_username, prod_name;
		int b_index; // Latest update.
		Buyer_Seller* new_bs = nullptr;
		Seller* new_seller = nullptr;
		Buyer* new_buyer = nullptr, *tmp_b=nullptr;
		/////////////////////////////////////////////////
		switch (option)
		{

		case 1://add buyer (Check for += operator)
			
			new_buyer = createBuyer();
			if(!((*this)+=new_buyer)) //using system's += operator (also check if the user already exist )
				cout << "Username already exist, please try again" << endl;
			break;

		case 2://add seller (Check for += operator)

			new_seller = createSeller();
			if (!((*this) += new_seller)) //using system's += operator (also check if the user already exist )
				cout << "Username already exist, please try again" << endl;
			break;

		case 3://add buyer-seller

			new_bs = createBuyerSeller();
			if (!((*this) += new_bs))
				cout << "Username already exist, please try again" << endl;
			break;

		case 4: //add product to seller
			cout << "Enter the username of the seller: ";
			getline(cin, s_username);
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
			getline(cin, b_username);

			cout << "Enter seller's username: ";
			getline(cin, s_username);

			b_index = isUserExist(b_username);

			if(b_index!=NOT_EXIST)
			tmp_b = dynamic_cast<Buyer*>(m_user_arr[b_index]);
			
			if (b_index == NOT_EXIST||!tmp_b||!(tmp_b->isOrderedFrom(s_username))) //check if there was indeed an order made by THIS BUYER from THIS SERLLER.
				cout << "Invalid action, " << b_username << " didn't buy from " << s_username << endl;
			else
			{
				addFeedbackToSeller(b_username, s_username, f = createFeedback(b_username));
				cout << "Feedback added successfully." << endl;
			}

			break;

		case 6: //add to cart
			cout << "Enter the username of the buyer: ";
			getline(cin, b_username);


			cout << "Enter the product name: ";
			getline(cin, prod_name);

			if (!addProductToBuyersCart(prod_name, b_username))
			{
				cout << "Buyer or prod not exist in the system." << endl;
			}

			break;

		case 7:	//order
			cout << "Enter the username of the buyer:";
			getline(cin, b_username);

			newOrder(b_username);

			break;

		case 8:	//payment
			cout << "Enter the username of the buyer:";
			getline(cin, b_username);

			payment(b_username);

			break;

		case 9: //print all buyers (Uses Buyer << operator)
			cout << endl;
			printBuyers();

			break;

		case 10://print all sellers (Uses Seller << operator)
			cout << endl;
			printSellers();

			break;

		case 11:
			cout << endl;
			printBuyerSellers();

			break;
		case 12: // print all products from specific name  (Uses Product << operator)
			cout << "Enter the product name: ";
			getline(cin, prod_name);

			cout << endl;
			printAllSpecificProduct(prod_name);

			break;

		case 13: //(Uses Buyer > operator)
			cout << "Enter first buyer's username: ";
			getline(cin, b_username);

			cout << "Enter second buyer's username: ";
			getline(cin, b2_username);

			cout << endl;
			compareBuyersByCart(b_username, b2_username);
			break;

		case 14: // exit
			saveUsers("users.txt"); //@@@@ do we want to get from the user a name for the file? :S
			cout << endl << "Thanks for using " << m_name << ", Bye Bye (:" << endl;
			exit_flag = false;
			break;

		default:
			cout << endl << "Ops... No such action" << endl << endl;
			break;
		}
	}
}