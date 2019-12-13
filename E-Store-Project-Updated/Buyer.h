#ifndef __Buyer_h
#define __Buyer_h
#include "Address.h"
#include "Product.h"

class Buyer
{
private:
	char* m_username;
	char* m_password;
	char* m_fname;
	char* m_lname;
	int m_cartPsize;
	int m_number_of_items;
	Address m_address;
	Product** m_cart;

public:

	inline const Product** getCart()const;
	inline const int getNumberOfItems()const;
	inline const char* getFirstName()const;
	inline const char* getLastName()const;
	inline const char* getUsername()const;
	inline const Address getAddress()const;

	//void deleteProductFromCart(Product* item_to_delete); Moved to Order.h
	void addToCart(Product* item_to_add);
	
	bool setPassword(const char* password);
	bool setFname(const char* fname);
	bool setLname(const char* lname);
	bool setAddress(const Address address);
	bool setCart(const Product** cart);
	
	void removeProductFromCart(Product* item_to_delete);
	void printBuyer()const;
	void reallocateCart();

	Buyer(char* userName, char* password, char* fname, char*
		lname, const Address &address)
	//c'tor & keep default for safety purposes. 
	Buyer(const Buyer& p); // copy c'tor
	~Buyer();
	
};

#endif //!__Buyer_h