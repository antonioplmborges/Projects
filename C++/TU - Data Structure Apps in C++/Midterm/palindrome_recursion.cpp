//Uses recursion to implement a palindrome checke and test the strings 1234321 and repaid.
//Name: Antonio Borges

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

bool palindrome(string);
//bool palindrome(int,int);

int _tmain(int argc, _TCHAR* argv[])
{

	string number = "1234321";
	string word = "repaid";

	/*CONVERTING TO INTEGER ONLY WORK FOR NUMERICAL CHARACTERS AND NOT ALPHABETICAL ONES BECAUSE THEIR INTEGER EQUIVALENTS
	ARE TOO LARGE. 

	int x = 0, y=0;
	char N[] = {'1','2','3','4','3','2','1','\0'};
	char W[] = {'r','e','p','a','i','d','\0'};

	int n=sizeof(N)-1;
	int w = sizeof(W)-1;

	for(int i=n-1,j=0 ; i>=0 ; i--,j++)
	{
		x = x + (N[i]-'0')*(int)(pow(10,j));
	}

	for (int i = w - 1, j = 0; i > 0; i--, j++)
	{
		y = y + (W[i] - '0')*(int)(pow(10, j));
	}
	cout << y << endl;

	*/

	//check if string is palindrome
	if (palindrome(number))
		cout << number << " is a palindrome." << endl;
	else
		cout << number << " is not a palindrome." << endl;

	if (palindrome(word))
		cout << word << " is a palindrome." << endl;
	else
		cout << word << " is not a palindrome." << endl;

	system("pause");
	return 0;
}

bool palindrome(string s)
{
	if (s.length() <= 1)
		// if length =0 OR 1 then it is
		return true;
	if (s[0] == s[s.length() - 1])
		// check for first and last char of String:
		// if they are same then do the same thing for a substring
		// with first and last char removed. and carry on this
		// until you string completes or condition fails
		return palindrome(s.substr(1, s.length() - 2));

	// if its not the case than string is not.
	return false;
}

/*
bool palindrome(int number, int numDigit)
{
	if (numDigit <= 1)
		return true;
	else
	{
		int firstDigit = number / (int)(pow(10, numDigit - 1));
		int lastDigit = number % 10;

		if (firstDigit != lastDigit)
			return false;
		else
		{
			number = (number % (int)(pow(10, numDigit - 1))) / 10;
			numDigit = numDigit - 2;
			return palindrome(number, numDigit);
		}

	}

}
*/