#include "stdafx.h"
#include "complexType.h"
#include <iostream>

using namespace std;

int main(void)
{
	complexType n1(23, 34);
	complexType n2, n3;
	complexType n4;

	cout << "n1 = " << n1 << endl;
	cout << "n2 = " << n2 << endl;

	cout << "Enter a complex number in the form(a, b) : ";
	cin >> n2;
	cout << endl;
	cout << "New value of n2 = " << n2 << endl;

	n4 = n2;
	cout << "n4 must have the same value as n2 : " << n4 << endl;

	n3 = n1 + n2;
	cout << "n3 = n1 + n2 is " << n3 << endl;
	if (n4 == n2)
		cout << "n4 is equal to n2." << endl;
	else
		cout << "n4 and n2 are different!" << endl;

	// Test Multiply operator
	cout << n1 << " * " << n2 << " = " << n1 * n2 << endl;

	system("pause");
	return 0;
}
