// Final Project
//Name: Antonio Borges

#include "stdafx.h"
#include "studentInfo.h"
#include<iostream>
#include<map> //multimap
#include <string>
#include <vector>
#include <algorithm>
#include <time.h> //random number
//#include <utility>

const int N = 15;// capacity of array fo students
static bool isMultiple = false;//flag to check if there 2 students with same name/key
static int I = 6;//next index of student array for insert()

using namespace std;

/*----------------------------------PROTOTYPE---------------------------------------*/
void populate(multimap<string, studentInfo>& studentRecord, studentInfo(&student)[N]);//populates the multimap
void showMenu();//shows menu
void insert(multimap<string, studentInfo>& studentRecord, studentInfo(&student)[N], string name, int id, double gpa);//inserts new student record into multimap
void findr(multimap<string, studentInfo>& studentRecord, string);//finds and displays a student record
void display(multimap<string, studentInfo>& );//displays name for unique keys and name & id for duplicates keys
void modify(multimap<string, studentInfo>&, string, int,double);//modifies the GPA of a student
void remove(multimap<string, studentInfo>&, string, int);//removes a student record
/*----------------------------------PROTOTYPE---------------------------------------*/

int _tmain(int argc, _TCHAR* argv[])
{
	
	studentInfo student[N];//array of students of size N

	multimap <string, studentInfo> studentRecord;//empty map

	populate(studentRecord, student);
	
	int selection;//user's menu's selection

	string name;
	int id;
	double gpa;
	string key;
	
	do{
		showMenu();
		cin >> selection;
		cout << endl;

		//executes the option selected
		switch (selection) {
		case 1://Insert
			
			//Prompt user for student's info
			cout << "\nName: ";
			cin.ignore();//clean cout buffer
			getline(cin,name);
			cout << "\nID: ";
			cin >> id;
			cout << "\nGPA: ";
			cin >> gpa;

			insert(studentRecord,student, name, id, gpa);
			break;

		case 2://Find

			cout << "Enter name: ";
			cin.ignore();
			getline(cin, key);
			cout << endl;
			
			findr(studentRecord, key);
			
			break;
		case 3://Modify

			cout << "Enter name: ";
			cin.ignore();
			getline(cin, key);
			

			findr(studentRecord, key);
			
			if (isMultiple)//duplicate key flag activated
			{
				//prompt for id to differentiate the records
				cout << "\nEnter the Id of the student you wish to modify: ";
				cin >> id;

				cout << "Enter new GPA: ";
				cin >> gpa;

				modify(studentRecord, key, id, gpa);
			}
			else//if unique key
			{
				multimap<string, studentInfo>::iterator it;
				it = studentRecord.find(key);//use iterator in order to get student id 
				cout << "\nEnter new GPA: ";
				cin >> gpa;

				modify(studentRecord, key, it->second.getStudentId(), gpa);
			}
			break;

		case 4://Remove

			cout << "Enter name: ";
			cin.ignore();
			getline(cin, key);

			findr(studentRecord, key);

			if (isMultiple)//duplicate key flag activated
			{
				//Prompt id
				cout << "\nEnter the Id of the student you wish to delete: ";
				cin >> id;

				remove(studentRecord, key, id);
			}
			else
			{
				multimap<string, studentInfo>::iterator it;//use iterator in order to defferentiate records
				it = studentRecord.find(key);
				remove(studentRecord, key, it->second.getStudentId());
			}
			break;
		case 5://Display

			display(studentRecord);
			break;

		case 6://Exit

			cout << "Exiting..." << endl;
			break;

		default:
			//you have entered wrong menu item
			system("cls");	//clear screen
			showMenu();
		}

	} while (selection != 6);

	system("pause");
	return 0;
}


void populate(multimap<string, studentInfo>& studentRecord, studentInfo(&student)[N])
{
	//6 harcoded student records
	studentRecord.insert(make_pair("Alex Daniel", student[0]));
	studentRecord.insert(make_pair("Alex Daniel", student[1]));
	studentRecord.insert(make_pair("Edson Vieira", student[2]));
	studentRecord.insert(make_pair("Gil Alves", student[3]));
	studentRecord.insert(make_pair("David Santiago", student[4]));
	studentRecord.insert(make_pair("Junior Miranda", student[5]));

	
	/* initialize random seed: */
	srand(time(NULL));

	multimap<string, studentInfo>::iterator it;

	for (it = studentRecord.begin(); it != studentRecord.end();++it)//traverses the student record map
	{
		int intRand = rand() % 100 + 1;//1-100
		double gpaRand = (double)(rand() % 4 + 1);//between 1-4

		it->second.setStudentId(intRand);//populates the id for each record with random numbers
		it->second.setStudentGpa(gpaRand);//populates the gpa for each reacord with random numbers

	}
}

void showMenu()
{
	cout << "\nMAIN MENU\n";
	cout << "1 - Insert\n";
	cout << "2 - Find\n";
	cout << "3 - Modify\n";
	cout << "4 - Remove\n";
	cout << "5 - Display\n";
	cout << "6 - Exit\n\n";
	cout << "Selection: ";
}

void insert(multimap<string, studentInfo>& studentRecord, studentInfo (&student)[N], string name, int id, double gpa)
{

	multimap<string, studentInfo>::iterator it = studentRecord.insert(make_pair(name, student[I]));//creates a new student record
	//populates the student info
	it->second.setStudentName(name);
	it->second.setStudentId(id);
	it->second.setStudentGpa(gpa);
}

void findr(multimap<string, studentInfo>& studentRecord, string key)
{
	multimap<string, studentInfo>::iterator it;
	it = studentRecord.equal_range(key).first;
	if (studentRecord.count(key) != 1)//if there's multiple record with the same key
	{
		isMultiple = true;//activates duplicate key flag 
		multimap<string, studentInfo>::iterator it;
		
		for (it = studentRecord.equal_range(key).first; it != studentRecord.equal_range(key).second; ++it)//traverse student record
		{
			cout << "Name: " << key << it->second;//display all duplicates student info
			cout << '\n';
		}
	}
	else
	{
		isMultiple = false;//deactivates duplicate key flag
		cout << "Name: " << key << it->second ;//display unique student info
		cout << '\n';
	}
		
}

void display(multimap<string, studentInfo>& studentRecord)
{
	vector<pair<string, int> > namesId;//creates a empty vector of type (string,int) for(keys,id)

	multimap <string, studentInfo>::iterator it;
	
	for (it = studentRecord.begin(); it != studentRecord.end(); it++) //traverse the student record map
	{

		namesId.push_back(pair<string,int>(it->first,it->second.getStudentId()));//copy only key and id to vector
		
		//copy(it->first, it->first, names.begin());
	}

	sort(namesId.begin(), namesId.end());//sorts vector in alphabetically
	
	vector<pair<string, int> >::iterator it4;//current item
	vector<pair<string, int> >::iterator it5 ;//checks previous item
	
	it5 = namesId.begin() + 1;//pos after first element
	for (it4 = namesId.begin(); it4 != namesId.end() && namesId.end() - it4 != 1 /* it4 != namesId.end()*/ /*&& ++it4 == namesId.end()*/; it4++)
	{
			//auto it2 = names.begin();
		if ((((*it4).first).compare((*(it4 + 1)).first) != 0) )//compare current and next keys, if not equal
		{
			if (((*it5).first).compare((*(it5 - 1)).first) == 0)//compare current and previous keys, if equal
			{
				cout << (*it4).first << " " << "(" << (*it4).second << ")\n";//Display name/key and id in parenthesis
				it5++;
				continue;
			}
			else
			{
				//Displays current student's name
				cout << (*it4).first << "\n";
				it5++;
				continue;
			}
	
		}
		else
		{
				//Displays the current and the next student's name and id
				cout << (*it4).first << " " << "(" << (*it4).second << ")\n";//Display current name/key and id in parenthesis
				cout << (*(it4 + 1)).first << " " << "(" << (*(it4 + 1)).second << ")\n";//Display next name/key and id in parenthesis
				//increments iterator by 1
				it5++;
				it4++;
				continue;			

		}
			
	}
		

	if ((it4-1)->first != namesId.back().first)
		cout << namesId.back().first << endl;//displays last value when student doesnt hv the same name
	
	
}

void modify(multimap<string, studentInfo>& studentRecord, string key, int id, double gpa)
{
	multimap<string, studentInfo>::iterator it;//creates a multimap iterator

	for (it = studentRecord.begin(); it != studentRecord.end(); it++)//traverse te map
	{
		if (it->second.getStudentId() == id)//if the id given by the user exists
		{
			it->second.setStudentGpa(gpa);//modifies the GPA 
			cout << "Done!\n";
			break;
		}
		//cout << "***The ID does not exit***\n";
	}
}

void remove(multimap<string, studentInfo>& studentRecord, string key, int id)
{
	multimap<string, studentInfo>::iterator it;//create multimap iterator

	for (it = studentRecord.begin(); it != studentRecord.end(); it++)//traverse the multimap
	{
		if (it->second.getStudentId() == id)//if the id given by the user exist
		{
			studentRecord.erase(it);//erasesa student record
			cout << "Done!\n";
			break;
		}
		//cout << "***The ID does not exit***\n";
	}
	I--;//decrements the index of the next record to be inserted, avoids memory leak
	
}