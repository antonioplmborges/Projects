// Prompts the user to enter the name of the file and display the contents of a text file on the screen. 
//Each line is 72 characters long. 
//Name: Antonio Borges

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

const int LINE = 72;


int main()
{
	ifstream infile;
	string str;
	

	string filename;
	//Get the filename from the user
	cout << "Enter the name of the file: ";
	cin >> filename;

	//open the file
	infile.open(filename.c_str());
	if (infile)//or fail(file)
	{
		while (!(infile.eof()))
		{
			//infile.read(buffer, LINE);
			//infile.getline(buffer, LINE);
			//infile.width(LINE);
			//infile >> buffer;
			//str.resize(LINE);
			//str.shrink_to_fit();
			getline(infile,str);//gets the paragraphs
			
			//for (string::iterator itr = str.begin(); itr!=str.end(); itr += LINE) ITERATOR APPROACH 
				//copy(itr, itr + LINE, ostream_iterator<char>(cout));

			for (unsigned pos = 0; pos <= str.size(); pos += LINE)//INDEX APPROACH
				cout << str.substr(pos, LINE) << endl;		
			
		}
		
		//close the file
		infile.close();
	}
	else
	{
		cout << "File open failure!" << endl;//error message
	}

	system("pause");
	return 0;
}

