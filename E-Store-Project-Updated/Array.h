#ifndef __Array_h
#define __Array_h
#include <iostream>
using namespace std;

template <class T>
class Array
{
	int m_phy_size, m_log_size;
	char m_del;
	T** m_arr;
	
public:
	Array(int size=1, char delimiter= ' ');
	Array(const Array& other);
	~Array();

public:
	const Array& operator=(const Array& other);
	const Array& operator+=(T* new_val);
	T* operator[](int i);
	const T* operator[](int i)const;

	friend ostream& operator<<(ostream& os, const Array& arr);

	inline const int getNumberOfItems()const { return m_log_size; }
	inline T** getArray()const { return m_arr; }

	void arrayRealloc();
	bool isEmpty()const;
	void removeFromArray(int index_to_delete);
	void setArray(T** other);
};

template<class T>
Array<T>::Array(int physize, char delimiter)
{
	m_phy_size = physize;
	m_log_size = 0;
	m_del = delimiter;

	m_arr = new T*[m_phy_size];
}

template<class T>
Array<T>::Array(const Array& other):m_arr(NULL)
{
	*this = other;
}

template<class T>
Array<T>::~Array()
{
	for (int i = 0; i < m_log_size; i++)
		delete m_arr[i];

	delete []m_arr; 
}

template<class T>
const Array<T>& Array<T>::operator=(const Array& other) // @@@ Why inside the class the signature is without <T> ???
{
	if (this != &other)
	{
		for (int i = 0; i < m_log_size; i++)
			delete m_arr[i];
		delete m_arr;

		m_phy_size = other.m_phy_size;
		m_log_size = other.m_log_size;
		m_del = other.m_del;

		m_arr = new T * [m_phy_size];
		for (int i = 0; i < m_log_size; i++)
			*(m_arr+i) = *(other.m_arr+i); //using T's operator =
	}
	return *this;
}

template<class T>
const Array<T>& Array<T>::operator+=(T* new_val)
{
	if (m_log_size == m_phy_size)
		arrayRealloc();
	m_arr[m_log_size++] = new_val;
	return *this;
}


template<class T>
void Array<T>::arrayRealloc()
{
	m_phy_size *= 2;
	T** tmp = new T * [m_phy_size];

	for (int i = 0; i < m_log_size; i++)
		tmp[i] = m_arr[i];
	delete[]m_arr;
	m_arr = tmp;
}

template <class T>
ostream& operator<<(ostream& os, const Array<T>& arr)
{
	for (int i = 0; i < arr.m_log_size; i++)
		os << *(arr.m_arr + i) << arr.m_del;

	return os;
}

template<class T>
 T* Array<T>::operator[](int i)
{
	 if (i<0 || i>m_log_size)
		 return nullptr;
	 return m_arr[i];
}

 template<class T>
 const T* Array<T>::operator[](int i)const 
 {
	 if (i<0 || i>m_log_size)
		 return nullptr;
	 return m_arr[i];
 }

template <class T>
bool Array<T>::isEmpty()const
{
	return m_log_size == 0;
}

template <class T>
void Array<T>::removeFromArray(int index_to_delete)
{
			T* tmp;
			for (int j = index_to_delete; j < m_log_size - 1; j++)
			{
				tmp = m_arr[j];
				m_arr[j] = m_arr[j + 1];
				m_arr[j + 1] = tmp;
			}
			m_arr[--m_log_size] = nullptr;
}

template<class T>
void Array<T>::setArray(T** other)
{
	m_arr = other;
}

#endif //!__Array_h