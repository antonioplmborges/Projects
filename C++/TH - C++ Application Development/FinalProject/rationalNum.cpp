//Include a constructor with two arguments that can be used to set the member variables of an object to any legitimate value.
//Also include a constructor that has only a single parameter of type int; call this single parameter whole_number
//Overload the input and output operators >> and <<. . Overload all of the following operators so that they 
//correctly apply to the type Rational: ==, <, >, +, -, *, and /. 

#include "stdafx.h"
#include "rationalNum.h"
#include <string>
#include <cstdlib>//stoi


rationalNum::rationalNum()
	:numerator(0), denominator(1)
{};

rationalNum::rationalNum(int n, int d)
{
	numerator = n;
	denominator = d;
}

rationalNum::rationalNum(int whole_number)
{
	numerator = whole_number;
	denominator = 1;
}

void rationalNum::normalize()
{
	int x, y, z;

	x = numerator;
	y = denominator;
	z = (x*x < y*y) ? (z = x) : (z = y);
	for (int i = 2; i*i <= z*z; i++){
		while ((x%i) == 0 && (y%i) == 0)
		{
			x = x / i;
			y = y / i;
			z = z / i;
		}
	}
	if (y<0){
		numerator = -x;
		denominator = -y;
	}
	else {
		numerator = x;
		denominator = y;
	}
		
}

rationalNum rationalNum::operator+(const rationalNum&right)
{
	rationalNum temp;
	temp.numerator = numerator*right.denominator + denominator*right.numerator;
	temp.denominator = denominator*right.denominator;
	temp.normalize();

	return temp;
}

rationalNum rationalNum::operator-(const rationalNum&right)
{
	rationalNum temp;
	temp.numerator = numerator*right.denominator - denominator*right.numerator;
	temp.denominator = denominator*right.denominator;
	temp.normalize();

	return temp;
}

rationalNum rationalNum::operator*(const rationalNum&right)
{
	rationalNum temp;
	temp.numerator = numerator*right.numerator;
	temp.denominator = denominator*right.denominator;
	temp.normalize();

	return temp;
}

rationalNum rationalNum::operator/(const rationalNum&right)
{
	rationalNum temp;
	temp.numerator = numerator*right.denominator;
	temp.denominator = denominator*right.numerator;
	temp.normalize();

	return temp;
}

void rationalNum::operator=(const rationalNum &rational_number) 
{

	numerator = rational_number.numerator;
	denominator = rational_number.denominator;

}

bool rationalNum::operator==(const rationalNum &right) const
{
	return (numerator*right.denominator == denominator*right.numerator);
}

bool rationalNum::operator>(rationalNum &right) 
{
	rationalNum temp;
	temp.numerator = numerator;
	temp.denominator = denominator;
	temp.normalize();
	right.normalize();
	//if(temp.denominator>0 && right.denominator>0)
		return (temp.numerator*right.denominator > temp.denominator*right.numerator);
	/*else if (temp.denominator < 0 && right.denominator < 0)
	{
		if (temp.numerator < 0 && right.numerator < 0)
			return (temp.numerator*right.denominator > temp.denominator*right.numerator);
		else if (temp.numerator < 0 && right.denominator > 0)
			return true;
		else if (temp.numerator > 0 && right.denominator < 0)
			return false;
		else if (temp.numerator > 0 && right.denominator > 0)
			return !(temp.numerator*right.denominator > temp.denominator*right.numerator);
	}
	else if (temp.denominator < 0 && right.denominator > 0)
	{
		if (temp.numerator < 0 && right.numerator > 0)
			return (numerator*right.denominator > temp.denominator*right.numerator);
		else if (temp.numerator < 0 && right.denominator < 0)
			return true;
		else if (temp.numerator > 0 && right.denominator > 0)
			return false;
		else if (temp.numerator > 0 && right.numerator < 0)
			return !(temp.numerator*right.denominator > temp.denominator*right.numerator);
	}
	else if (temp.denominator > 0 && right.denominator < 0)
	{
		if (temp.numerator > 0 && right.numerator < 0)
			return (temp.numerator*right.denominator > temp.denominator*right.numerator);
		else if (temp.numerator > 0 && right.denominator > 0)
			return true;
		else if (temp.numerator < 0 && right.denominator < 0)
			return false;
		else if (temp.numerator < 0 && right.numerator > 0)
			return !(temp.numerator*right.denominator > temp.denominator*right.numerator);
	}
	*/
}

bool rationalNum::operator<(rationalNum &right) 
{
	rationalNum temp;

	temp.numerator = numerator;
	temp.denominator = denominator;
	temp.normalize();
	right.normalize();
	//if (temp.denominator>0 && right.denominator>0)
		return !(temp.numerator*right.denominator > temp.denominator*right.numerator);
}

std::ostream& operator<<(std::ostream& cout, const rationalNum& rational_number)
{
	return std::cout << rational_number.numerator << "/" << rational_number.denominator;
}

std::istream& operator>>(std::istream& cin, rationalNum& rational_number)
{
	std::string input;

	for (;;)//loop
	{
		std::getline(cin, input);
		/*if (input.length() < 10)//if input's lenght is not 5....
		{
			std::cout << "***Incorrect input size***\n";
			std::cout << "Retry: ";
			continue;
		}*/
		if ((input.find_first_of('/') != input.find_last_of('/')))//if the first an last character are not '(' and ')', respectively
		{																															//and there's more than a ','

			std::cout << "***Bad format***\n";
			std::cout << "Retry: ";
			continue;
		}
		else
		{
			std::string numerator_string, denominator_string;
			numerator_string = input.substr(0, input.find('/'));//substr(position,lenght) ->string class
			denominator_string = input.substr(input.find('/')+1, input.length());
			//DEBUG std::cout << numerator_string << "   " << denominator_string;

			try
			{
				rational_number.numerator = stoi(numerator_string); //stoi(str) is a function that converts strings into integers
				rational_number.denominator = stoi(denominator_string);
			}
			catch (std::invalid_argument& e){
				std::cout << "***Bad input*** ->" << e.what() << "\n";
				std::cout << "Retry: ";
				continue;
			}

			if (rational_number.denominator == 0)
			{
				std::cout << "***Denominator cannot be 0***\n";
				std::cout << "Retry: ";
				continue;
			}

			break;
		}

	}
	return cin;
}