// Program that prints the Fibonocci sequence, using recursion,  for a specific number of terms in the sequence
//Name: Antonio Borges

#include "stdafx.h"
#include <iostream>

using namespace std;

int fib(int);

int main(int argc, _TCHAR* argv[])
{
	int N;

	cout << "Enter the number of terms in the sequence: ";//prompt
	cin >> N;//store input
	
	while (N <= 0)//input validation for0 and negative numbers.
	{
		cout << "***Enter a positive number. Retry!***" << endl;
		cout << "Enter the number of terms in the sequence: ";
		cin >> N;
	}
	
	for (int i = 1; i <= N;i++)//print term sequence
		cout<<fib(i)<<" ";

	cout << endl;
	system("pause");
	return 0;
}

int fib(int n)
{
	if (n == 1)
		return 1;
	else if (n == 2)
		return 1;
	else
		return (fib(n - 1) + fib(n - 2));
}