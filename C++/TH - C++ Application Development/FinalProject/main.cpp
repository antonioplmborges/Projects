//Final Project: Rational Number
//Name: Antonio Borges


#include "stdafx.h"
#include "rationalNum.h"
#include <iostream>

using namespace std;

int main(void)
{
	rationalNum n1(1, 2);
	rationalNum n2(5);
	rationalNum n3, n4;
	rationalNum n5;

	cout << "n1 = " << n1 << endl;
	cout << "n2 = " << n2 << endl;
	cout << "n3 = " << n3 << endl;

	cout << "Enter a rational number in the form a/b : ";
	cin >> n3;
	cout << endl;
	cout << "New value of n3 = " << n3 << endl;

	if (n1 == n3)
		cout << "n1 is equal to n3." << endl;
	else if (n1 > n3)
		cout << "n1 is greater than n3!" << endl;
	else if (n1 < n3)
		cout << "n1 is smaller than n3!" << endl;

	n4 = n3;
	cout << "n4 must have the same value as n2 : " << n4 << endl;

	if (n4 == n2)
		cout << "n4 is equal to n2." << endl;

	n5 = n1 + n3;
	cout << "n5 = n1 + n3 is " << n3 << endl;
	
	if (n5 == n3)
		cout << "n3 is equal to n3." << endl;
	else if (n5 > n3)
		cout << "n3 is greater than n3!" << endl;
	else if (n5 < n3)
		cout << "n3 is smaller than n3!" << endl;

	// Test Multiply operator
	cout << n1 << " * " << n3 << " = " << n1 * n3 << endl;

	// Test Division operator
	cout << n1 << " / " << n3 << " = " << n1 / n3 << endl;


	system("pause");
	return 0;
}
