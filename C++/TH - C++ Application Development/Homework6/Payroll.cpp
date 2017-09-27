//Write a program (payroll.cpp) with an array of 4 Payroll objects. Allocate the Payroll objects dynamically. 
//The program should ask the user for the employee’s ID, hourly rate, and number of hours worked using the overload >> operator. 
//The program should calculate the total pay for the week. Use the << operator to display to cout the full information about each employee.
//Name: Antonio Borges

#include "stdafx.h"
#include "Payroll.h"
#include <iostream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	
	Payroll user(N);// constructs N array of Payroll objects

	cout << "Enter employee id, hourly rate & number of hours worked \n";
	cin >> user;//input all 3 values
	cout << endl;
	cout << "-----------------------------------" << endl;
	cout << user;//prints the values in each object

	user.~Payroll();//destructor
	
	system("pause");
	return 0;
}

