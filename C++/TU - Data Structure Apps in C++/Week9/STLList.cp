// STL linked list example

#include <iostream>
#include <list>
#include <algorithm>	// for copy and find
#include <iterator>	// for ostream_iterator

using namespace std;

// Prototypes
void print(list<int>& );
bool findValue(list<int>& , int);  // Uses STL find() function

int main (void)
{
	list<int> LL;
	LL.push_front(2);
	LL.push_front(4);
	LL.push_front(6);
	LL.push_front(8);
	LL.push_front(10);
	print(LL);
	cout << "top=" << *LL.begin() << endl;

	if (findValue(LL,2)) cout << 2 << " is in the list\n";
	if (findValue(LL,5)) cout << 5 << " is in the list\n";
	if (findValue(LL,6)) cout << 6 << " is in the list\n";
	if (findValue(LL,10)) cout << 10 << " is in the list\n";
	cout << "Removing 3 and 6. 3 is not in the list.\n"; 
	LL.remove(3);
	LL.remove(6);
	cout << "\nPrint the list. It should have 10 8 4 2.\n";
	print(LL);
	cout << "Next remove 10 and 2. \n"; 	
	LL.remove(2);
	LL.remove(10);
	cout << "\nPrint the list. It should have 8 4.\n";
	print(LL);

	return 0;
}

void print(list<int>& lint)
{
	// The ostream_iterator below writes to "cout" and the delimiter is a "space" character
	// You can write to any output stream, not just cout.

	// copy is an STL function (algorithm.

	copy(lint.begin(),lint.end(),ostream_iterator<int>(cout," ")); 
	cout << endl;
}

bool findValue(list<int>& lint, int value)
{
	// Calls the STL find() function
	return find(lint.begin(),lint.end(),value)!=lint.end();
}

