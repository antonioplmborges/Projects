//Driver program to test the Stack class template for int and doubles
//Name:Antonio Borges


#include "stdafx.h"
#include "stack.h"

using namespace std;

int main()
{
	Stack <int> intStack;
	Stack <double> doubleStack;

	cout << "Integer Stack" << endl;
	cout<<"Empty: "<<intStack.empty()<<endl;
	intStack.push(1);
	intStack.push(2);
	cout << "Empty: " << intStack.empty() << endl;
	cout << "Top: " << intStack.top() << endl;
	intStack.display(cout);


	cout << "Double Stack" << endl;
	cout << "Empty: " << doubleStack.empty() << endl;
	doubleStack.push(5.0);
	doubleStack.push(6.0);
	cout << "Empty: " << doubleStack.empty() << endl;
	cout << "Top: " << doubleStack.top() <<endl;
	doubleStack.display(cout);

	system("pause");
	return 0;
}