// Program that reads a person’s name in the following format: First name, then middle name or initial, and then last name
//Then outputs the name in the following format: Last Name  First_Name  Middle_Initial.
//Name: Antonio Borges

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
	string input;
	
	for(;;)//loop
	{
		cout << "Enter your full name: ";//Prompt name
		getline(cin, input);//saves the user input on string 'input'

		int x = input.find_first_of(" ");//finds the position/index of the first space in the string
		int y = input.find_last_of(" ");//finds the the position/index of the last space in the string

		if(x==-1 && y ==-1)
		{
			cout << "**Input too small**"<<endl;
			cout<<"Try Again"<<endl;
			continue;
		}

		if (x == y)//if the first space is has the same index as the last space, then there are only 2 strings...
		{
			string string1 = input.substr(0,x);//string 1 goes from index 0 until first space
			string string2 = input.substr(x, input.length() - x);//string 2 goes from index of the first space until the end of the string

			cout << string2 << ", " << string1 <<endl;//Print the name
			break;//gets out of the loop
		}
		else//if there are more than 2 strings
		{
			string string1 = input.substr(0, x);
			string string2 = input.substr(x + 1, y - (x + 1));//string 2 goes from index of the first char after the space(x+1) until the next space
			string string3 = input.substr(y, input.length() - y);

			//check for space in the strings2, which meanns that its more than 1 string;
			if (string2.find(" ") != string::npos)
			{
				cout << "**Input too large**"<<endl;
				cout<<"Try Again"<<endl;
				continue;
			}
			else
			{
				cout << string3 << ", " << string2[0] << ". " << string1 << endl;///Print the name
				break;
			}
	
		}

	}
	system("pause");
	return 0;
}
