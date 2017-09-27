
#include "stdafx.h"

#include <iostream>

#ifndef STACK
#define STACK

using namespace std;

#define N 10 // Size of Array

template < typename T >
class Sort
{
public:
		// Prototypes
		void fill_array(T a[], int size, int& number_used);

		void sort(T a[], int number_used);

		void swap(T& v1, T& v2);

		int index_of_smallest(const T a[], int start_index, int number_used);

private:
	T a[N];
};

#endif 
