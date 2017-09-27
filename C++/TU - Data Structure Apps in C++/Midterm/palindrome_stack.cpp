//Construct three char-valued STL stacks stack1, stack2, and stack3. Push char to be tested into stack1 and stack2. Then pop from stack2 and push in stack3.
// If the contents of stack1 and stack3 are identical, then the original input string is a palindrome; otherwise it is not.	
//Test the algorithm for the strings racecar and stressed.
//Name: Antonio Borges

#include "stdafx.h"
#include <iostream>
#include <stack>

using namespace std;

//func prototype
void palindrome(char [], stack<char>&, stack<char>&, stack<char>&);


//const int N = 32


int _tmain(int argc, _TCHAR* argv[])
{
	stack <char> stack1, stack2, stack3;
	
	char string_test1 [] = {'r','a','c','e','c','a','r', '\0' };
	char string_test2 [] = {'s','t','r','e','s','s','e','d','\0' };

	//check if palindrome
	palindrome(string_test1,stack1,stack2,stack3);
	palindrome(string_test2,stack1,stack2,stack3);
	
	system("pause");
	return 0;
}

//func definition
void palindrome(char string [], stack<char>&stack1, stack<char>&stack2, stack<char>&stack3)
{
	//push char to be tested onto stack1 and stack2
	for(int i=0;i < strlen(string);i++)
	{
		stack1.push(string[i]);
		stack2.push(string[i]);
	}
	//Pop the contents of stack2, and push each of the characters popped from stack2 onto stack3
	while(!stack2.empty())
	{
		//stack3.push(stack2.pop());
		stack3.push(stack2.top());
		stack2.pop();
	}
	//check if stack1 and stack3 are equal
	if(stack1==stack3)
		cout<<string<<" is palindrome"<<endl;
	else
		cout<<string<<" is not palindrome"<<endl;

}