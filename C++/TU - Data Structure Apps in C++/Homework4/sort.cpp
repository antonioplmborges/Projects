#include "stdafx.h"
#include <iostream>
//#include <typeinfo>
using namespace std;

#include "sort.h"

/*partial template specialization

template< class T >
struct TypeIsDouble
{
	static const bool value = false;
};

template<>
struct TypeIsDouble< double >
{
	static const bool value = true;
};

template< class T >
struct TypeIsChar
{
	static const bool value = false;
};

template<>
struct TypeIsChar< char >
{
	static const bool value = true;
};
*/

template < typename T >
void Sort <T> :: fill_array(T a[], int size, int& number_used)
{
	// size = Declared size of the array
	// number_used = is the number of values stored in
	// a[0] through a[number_used - 1]

	// In this program we assume the array a[] will be filled with the
	// the following values.

	double x[] = { 8, 6, 10, 2, 16, 4, 18, 14, 12, 20 };
	char y[] = { 'z', 'o', 't', 'e', 'a', 'c','b', 'm', 'g', 'i'};

	// We need the size of the array x[]. There is a function
	// sizeof(x) which will give us the size of x in bytes.
	// We need the size in words

	//if (TypeIsDouble<T>::value)
	if (typeid(T)==typeid(double))
	{
		number_used = sizeof(x) / sizeof(double);
		for (int i = 0; i < number_used; i++)
			a[i] = x[i];
	}
	
	//else if (TypeIsChar<T>::value)
	else if (typeid(T) == typeid(char))
	{
		number_used = sizeof(y) / sizeof(char);
		for (int i = 0; i < number_used; i++)
			a[i] = y[i];
	}
	else
	{
		cout << "***TYPE NOT IMPLEMENTED***" << endl;
		exit(EXIT_FAILURE);
	}
		
	

	return;
}

template < typename T >
void Sort <T>:: sort(T a[], int number_used)
{
	int index_of_next_smallest;
	for (int i = 0; i < number_used - 1; i++)
	{
		// Place the correct value in a[i]
		index_of_next_smallest = index_of_smallest(a, i, number_used);
		swap(a[i], a[index_of_next_smallest]);
	}
	return;
}

template < typename T >
void Sort <T>:: swap(T& v1, T& v2)
{
	T temp = v1;
	v1 = v2;
	v2 = temp;
}

template < typename T >
int Sort <T>:: index_of_smallest(const T a[], int start_index, int number_used)
{
	T min = a[start_index];
		int index_of_min = start_index;

	for (int i = start_index + 1; i < number_used; i++)
		if (a[i] < min)
		{
		min = a[i];
		index_of_min = i;
		// min is the smallest of a[start_index] through a[i]
		}

	return index_of_min;
}

template class Sort < double > ;
template class Sort < char > ;