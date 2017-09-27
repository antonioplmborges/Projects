//Program reads two files, file1.txt and file2.txt, and merges these two files to a third file named output.txt. 
//The output file it's suppose to contain all numbers from 0 to 10 in order.
//Name: Antonio Borges

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

int main()
{
	//open the files
	fstream file1("file1.txt",ios::in);
	fstream file2("file2.txt", ios::in);
	//creates output.txt
	fstream output("output.txt", ios::out);

	int num1, num2;

	//if file1 and file2 sucessfully opened, process it
	if (file1 && file2)
	{
		cout << "[File1.txt]" << endl;
		while (!file1.eof())
		{
			file1 >> num1;
			cout << num1 << endl;
		}

		cout << "[File2.txt]" << endl;
		while (!file2.eof())
		{
			file2 >> num2;
			cout << num2 << endl;
		}

		//closes files
		file1.close();
		file2.close();
	}
	
	//re-open file1 and file2
	file1.open("file1.txt");
	file2.open("file2.txt");

	if (file1 && file2 && output)
	{

		cout << "[Output.txt]" << endl;
		while (!file1.eof()||!file2.eof())
		{
			//if its reaches the end of file2
			if (file2.eof())
			{
				file1 >> num1;
				output << num1 << endl;//print only line from file1
				cout << num1 << endl;
			}
			else if (file1.eof())//if its reaches the end of file1
			{
				file2 >> num2;
				output << num2 << endl;//print only line from file2
				cout << num2 << endl;
			}
			else//if it doesnt reach the end of file1 or file2
			{
				file1 >> num1;//get value from file1
				file2 >> num2;//get value from file2

				if (num1 > num2)//print the smallest number first then the larger one
				{
					output << num2 << endl;
					output << num1 << endl;
					cout << num2 << endl;
					cout << num1 << endl;
				}
				else
				{
					output << num1 << endl;
					output << num2 << endl;
					cout << num1 << endl;
					cout << num2 << endl;
				}
			}

		}//end while

		
		//closes all files
		file1.close();
		file2.close();
		output.close();

	}//end if
	else
	{
		//Display error message
		cout << "Error opening the file" << endl;
	}

	

	cout<<"DONE"<<endl;
	system("pause");

	return 0;
}

