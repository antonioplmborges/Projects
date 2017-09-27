// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "sort.h"

using namespace std;

// Start of program

int main()
{
	cout << "This program sorts numbers from lowest to highest.\n"<<endl;

	
	int number_used;//number of values stored in array
	double double_array[N];
	char char_array[N];
	
	Sort <double> doubleSort;
	Sort <char> charSort;

	doubleSort.fill_array(double_array, N, number_used);
	doubleSort.sort(double_array, number_used);

	cout << "In sorted order the numbers are: \n";
	for (int i = 0; i < number_used; i++)//display the values in the array
		cout << double_array[i] << " ";
	
	cout << endl;
	cout << endl;

	charSort.fill_array(char_array, N, number_used);
	charSort.sort(char_array, number_used);

	cout << "In sorted order the characters are: \n";
	for (int i = 0; i < number_used; i++)//display the values in the array
		cout << char_array[i] << " ";
	
	cout << endl;

	system("pause");
	return 0;
}
