//Given a vector of integers with the following values:
//{32, 9, 100, 75, 3, 487, 62, 18, 77, 99, 115, 345, 408}
//Use the binary search algorithm to find the values 99 and 114.
// Name:Antonio Borges


#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <functional>//std::greater

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	vector <int> number = { 32, 9, 100, 75, 3, 487, 62, 18, 77, 99, 115, 345, 408 };
	copy(number.begin(), number.end(), ostream_iterator<int>(cout, " "));
	cout << "\n";
	sort(number.begin(), number.end(), greater<int>());//descending order
	copy(number.begin(), number.end(), ostream_iterator<int>(cout, " "));//print values in vector
	cout << "\n";

	//sort(number.begin(), number.end());//ascinding order
	
	if (binary_search(number.rbegin(), number.rend(), 99))//rbegin and rend to make it into ascending order
		cout << "Vector contains 99\n";
	else
		cout << "Vector does not contain 99\n";

	if (binary_search(number.begin(), number.end(), 104))
		cout << "Vector contains 104\n";
	else
		cout << "Vector does not contain 104\n";

	system("pause");
	return 0;
}

