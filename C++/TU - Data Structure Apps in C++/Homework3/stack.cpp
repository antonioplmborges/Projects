/*----------------Stack.cpp  FIG. ------------------------------------

This file implements Stack member functions.

-------------------------------------------------------------------------*/
#include "stdafx.h"
#include <iostream>
using namespace std;

#include "stack.h"

//--- Definition of Stack constructor
template < typename StackElement >
Stack<StackElement>::Stack()
	: myTop(-1)
{}

//--- Definition of empty()
template < typename StackElement >
bool Stack<StackElement>::empty() const
{
	return (myTop == -1);
}

//--- Definition of push()
template < typename StackElement >
void Stack<StackElement>::push(const StackElement & value)
{
	if (myTop < STACK_CAPACITY - 1) //Preserve stack invariant
	{
		++myTop;
		myArray[myTop] = value;
	}
	else
	{
		cerr << "*** Stack full -- can't add new value ***\n"
			"Must increase value of STACK_CAPACITY in Stack.h\n";
		exit(1);
	}
}

//--- Definition of display()
template < typename StackElement >
void Stack<StackElement>::display(ostream & out) const
{
	for (int i = myTop; i >= 0; i--)
		out << myArray[i] << endl;
}

//--- Definition of top()
template < typename StackElement >
StackElement Stack<StackElement>::top() const
{
	if (!empty())
		return (myArray[myTop]);
	else
	{
		cerr << "*** Stack is empty "
			" -- returning garbage value ***\n";
		return *(new StackElement);
	}
}

//--- Definition of pop()
template < typename StackElement >
void Stack<StackElement>::pop()
{
	if (!empty())
		myTop--;
	else
		cerr << "*** Stack is empty -- "
		"can't remove a value ***\n";
}

//Explicit instatiation
template class Stack < int > ;
template class Stack < double >;
