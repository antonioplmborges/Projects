// Design class date with integers month, day, year and test the class in a small application that defines Date object's and its interface
//Name: Antonio Borges

#include <cstdlib>
#include <iostream>
#include <string>


using namespace std;

class Date
{
private:
	int month;
	int day;
	int year;

public: //Member functions
	int getDay() const;//returns day
	int getMonth()const;//returns month
	int getYear()const;//returns year
	void setDate(int, int, int);//sets the date
	void setDay(int);//sets the day
	void setMonth(int);//sets the months
	void setYear(int);//sets the year
	void printDate();//outputs the date
	void printDateExtend();//outputs the date in a different format
	void userDate();//deals with validation of the user input
};//end of class declaration


int Date::getDay()const
{
	return  day;
}

int Date::getMonth() const
{
	return  month;
}

int Date::getYear() const
{
	return  year;
}
void Date::setDay(int d)
{
	if (d > 0 && d < 32)
		day = d;
	else
	{
		cout << "***Day is out-of-range***" << endl;//prints error
		system("pause");
		exit(EXIT_FAILURE);
	}
}

void Date::setMonth(int m)
{
	if (m>0 && m < 13)
		month = m;
	else
	{
		cout << "***Month is out-of-range***" << endl;//prints error
		system("pause");
		exit(EXIT_FAILURE);
	}
}

void Date::setYear(int y)
{
	if (y>0 && y < 3000)
		year = y;
	else
	{
		cout << "***Year is out-of-range [0 - 2999]***" << endl;//prints error
		system("pause");
		exit(EXIT_FAILURE);
	}
}

void Date::printDate()
{
	cout << month << "/" << day << "/" << year << endl;
}

void Date::printDateExtend()
{
	string months[] = {
		"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
	};
	cout << day << " " << months[month - 1] << " " << year << endl;//prints the actual month
	;
}

void Date::setDate(int m, int d, int y)
{
	month = m;
	day = d;
	year = y;
}

void Date::userDate()
{
	string input, monthStr, dayStr, yearStr;
	for (;;)//loop
	{
		cin >> input;
		if (input.length() != 10)//if input's lenght is not 10....
		{
			cout << "***Incorrect input size***" << endl;
			cout << "Retry: ";
			continue;
		}
		else if (((input[2] != '/') || (input[5] != '/')) && ((input[2] != '-') || (input[5] != '-')))//if the character on index 2 and 5 are not '/' and '-'
		{

			cout << "***Bad format***" << endl;
			cout << "Retry: ";
			continue;


		}
		else if ((input[0] < '0') || (input[0] > '1') || //if the user enters an invalid date, out-of-range
			(input[1]<'0') || (input[1]>'9') ||
			(input[3] < '0') || (input[3]>'3') ||
			(input[4]<'0') || (input[4]>'9') ||
			(input[6] < '0') || (input[6]>'2') ||
			(input[7]<'0') || (input[7]>'9') ||
			(input[8]<'0') || (input[8]>'9') ||
			(input[9]<'0') || (input[9]>'9'))
		{
			cout << "***Bad input***" << endl;
			cout << "Retry: ";
			continue;
		}
		else
		{
			monthStr = input.substr(0, 2);//substr(position,lenght) ->string class
			dayStr = input.substr(3, 2);
			yearStr = input.substr(6, 4);

			setMonth(stoi(monthStr)); //stoi(str) is a function that converts strings into integers
			setDay(stoi(dayStr));
			setYear(stoi(yearStr));
			break;
		}

	}
}
;

int main()
{
	Date birthday;
	int birthday_day = 10;
	int birthday_month = 4;
	int birthday_year = 1994;

	birthday.setDate(birthday_month, birthday_day, birthday_year);//hardcodes the date '04/10/1994'
	cout << "BIRTHDAY:" << birthday.getMonth() << "/" << birthday.getDay() << "/" << birthday.getYear() << endl;//returns the date 
	birthday.printDateExtend();//prints the extended format
	birthday.printDate();//prints normal format
	cout << "Enter birthday: ";
	birthday.userDate();//validates user input
	birthday.printDateExtend();//prints date in extended format
	cout << "Enter month: ";
	cin >> birthday_month;
	birthday.setMonth(birthday_month);//assigns new value for month
	cout << "Enter day: ";
	cin >> birthday_day;
	birthday.setDay(birthday_day);//assigns new value for day
	cout << "Enter year: ";
	cin >> birthday_year; 
	birthday.setYear(birthday_year);//assigns new value for year
	birthday.printDateExtend();//prints date extended format
	birthday.printDate();




	system("pause");
	return 0;
}
