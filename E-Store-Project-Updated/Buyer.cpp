#include "Buyer.h"
#include "Utils.h"
#include "Seller.h"
#include "Order.h"
#include <iostream>


using namespace std;

// -------------------- C'tor, Copy C'tor, D'tor --------------------//
Buyer::Buyer(const string& userName, const string& password, const string& fname,
	const string& lname, const Address& address) : User(userName, password, fname, lname, address), m_cart(1, ' ')
{
}

Buyer::Buyer(const Buyer& other) : User(other) // copy c'tor
{ // Don't call the assignment operator because it calls the assignment of User, and we want to keep
	// the call in the init list. - After consulting with the lecturer. 

	m_checkout_orders.reserve(other.m_checkout_orders.capacity()); // Efficiency

	for (auto order : other.m_checkout_orders)
		m_checkout_orders.push_back(new Order (*order)); // Deep copy. order

	m_cart = other.m_cart;

}

Buyer::~Buyer() // d'tor
{
	for (auto order:m_checkout_orders)
		delete order;
	cout << "/n##Buyer Dtor with: " << this->m_username; "####/n";//@@@
}

//----------------------- Setters Methods ------------------------------//

bool Buyer::setCart(Product** cart)
{ // Set cart for buyer. Validation check - cart exists.
	if (!cart)
		return false;
	m_cart.setArray(cart);
	return true;
}

bool Buyer::setOrders(vector<Order*> other) // protected - Orders cannot get changed after initialization
{  // set orders for Buyer. Validation check - pointer exists.
	if (other.empty())
		return false;
	m_checkout_orders = other;
	return true;
}


// ----------------------- Arrays maintenance methods. ----------------------- //

bool Buyer::addToCart(Product* item_to_add)
{ // Add to Buyer's cart using realloc method.
	if (!item_to_add)
		return false;
	m_cart += item_to_add;
	return true;
}

bool Buyer::addToCheckout(Order* checkout_order)
{ // Add to Buyer's checkout cart using realloc method.
	if (!checkout_order)
		return false;

	if (m_checkout_orders.size() == m_checkout_orders.capacity()) // Efficiency 
		m_checkout_orders.reserve(m_checkout_orders.capacity() * 2); 
	m_checkout_orders.push_back(checkout_order);

	return true;
}

bool Buyer::removeFromCart(Product* item_to_delete)
{ /* Remove a product from Buyer's cart by bubbling it to the end of the arr,
	and setting it to nullptr.*/
	bool flag = false;
	for (int i = 0; i < m_cart.getNumberOfItems(); i++)
	{
		if (m_cart[i]->getSerialNumber() == item_to_delete->getSerialNumber())
		{
			m_cart.removeFromArray(i); // Remove the product in the i place
			break;
		}
	}
	return flag;
}

// ----------------------- Printing methods. ----------------------- // 

void Buyer::showCart()const
{ // Print buyer's cart.

	if (m_cart.isEmpty())
		cout << endl << "No products to show, your cart is currently empty." << endl <<
		"Please search for products to buy or go to your checkout cart to continue with your order" << endl;
	else {
		cout << "All products are in #/Name/Price/Seller format" << endl;

		for (int i = 0; i < m_cart.getNumberOfItems(); i++)
			cout << i + 1 << ") " << m_cart[i]->getName() << "\t" << m_cart[i]->getPrice() <<
			"$\t" << m_cart[i]->getSellerUsername() << endl;
	}
}


void Buyer::showCheckoutOrders()const
{ // Show all orders that hasn't been paid yet.
	int i = 0;

	for (auto order_ptr:m_checkout_orders)
		if (!order_ptr->getPaid())
		{
			cout << "\n\t Order #" << i + 1 << endl;
			order_ptr->showOrder();
		}

}

// -------------------- Boolean checks -------------------- //

bool Buyer::isOrderedFrom(const string& username)const
{ // Check if there's an existing order from a given seller, and that it's paid for.

	int i = 0;
	for (auto order_ptr : m_checkout_orders)
	{
		for (auto product_ptr : order_ptr->getProductsArr())
		{
			if (product_ptr->getSellerUsername() == username)
				if (order_ptr->getPaid())
					return true;
		}
	}

	return false;
}

bool Buyer::isEmptyCheckoutOrders()
{ //  Is empty even if there are actual orders in the arr, but they're all paid for. 

	for (auto order_ptr : m_checkout_orders)
		if (!order_ptr->getPaid())
			return false;

	return true;

}

bool Buyer::isEmptyCart()
{ // Check for empty cart.
	return m_cart.isEmpty();
}

// ---------------------------------------------------------------------- //

double Buyer::getTotalCartValue()const
{ // Get the total price value of the cart.
	double res = 0;

	for (int i = 0; i < this->m_cart.getNumberOfItems(); i++)
		res += this->m_cart[i]->getPrice();
	return res;
}

// -------------------- Operators -------------------- //

bool Buyer::operator>(const Buyer& other)const
{ // Compare between two cart values of different Buyers.
	return this->getTotalCartValue() > other.getTotalCartValue();
}

const Buyer& Buyer::operator=(const Buyer& other)
{ // Assignment operator - Call for the User's assignment operator and use the Product assignment as well.
	if (this != &other)
	{
		User::operator=(other);
		m_cart = other.m_cart;

		for (auto order_ptr : other.m_checkout_orders)
			m_checkout_orders.push_back(new Order(*order_ptr));

	}
	return *this;

}
void Buyer::toOs(ostream& os)const
{ // Print user type. 
	os << "\n\tUser type: " << typeid(*this).name() + 6;
}

