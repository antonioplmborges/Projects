#include "stdafx.h"
#include "complexType.h"
#include <string>
#include <cstdlib>

complexType::complexType()
	//:real(0), imag(0)
{
	real = 0;
	imag = 0;
}

complexType::complexType(int a , int b)
{
	real = a;
	imag = b;
}

std::ostream& operator<<(std::ostream& cout, const complexType& complex_number)
{
	if (complex_number.real == 0 && complex_number.imag == 0)//if real part and imaginary is 0
		std::cout << complex_number.real;					//print 0
	else if (complex_number.real==0)	//if real part is 0
		std::cout << complex_number.imag << "i"; //print imaginary part
	else if (complex_number.imag == 0)	//if imaginary part is 0
		std::cout << complex_number.real;	//print real part
	else
		std::cout << complex_number.real<< " + " << complex_number.imag << "i";//print real and imaginary part
	return cout;
}

std::istream& operator>>(std::istream& cin, complexType& complex_number)
{
	std::string input;

	for (;;)//loop
	{
		std::getline(cin,input);
		//std::cout << input.length();
		if (input.length() < 5)//if input's lenght is not 5....
		{
			std::cout << "***Incorrect input size***\n";
			std::cout << "Retry: ";
			continue;
		}
		else if (((input[0] != '(') || (input[input.length() - 1] != ')')) || (input.find_first_of(',') != input.find_last_of(',')))//if the first an last character are not '(' and ')', respectively
		{																															//and there's more than a ','

			std::cout << "***Bad format***\n";
			std::cout << "Retry: ";
			continue;


		}
		else
		{
			std::string real_string, imag_string;
			real_string = input.substr(1, input.find(',')-1);//substr(position,lenght) ->string class
			imag_string = input.substr(input.find(',')+1, input.length() - 2);

			
			try 
			{
				complex_number.real = stoi(real_string); //stoi(str) is a function that converts strings into integers
				complex_number.imag = stoi(imag_string);
			}
			catch (std::invalid_argument& e){
				std::cout << "***Bad input*** ->"<<e.what()<<"\n";
				std::cout << "Retry: ";
				continue;
			}
			
			break;
		}

	}
	return cin;
}

complexType complexType::operator+(const complexType& c)
{
	complexType complex_number;
	complex_number.real = this->real + c.real;
	complex_number.imag = this->imag + c.imag;
	return complex_number;
}

complexType complexType::operator*(const complexType& c)
{
	complexType complex_number;
	complex_number.real = this->real*c.real - this->imag*c.imag;
	complex_number.imag = this->real*c.imag + this->imag*c.real;
	return complex_number;
}

bool complexType::operator==(const complexType& c)
{
	return (c.real == real && c.imag == imag);
}

void complexType::operator=(const complexType &c)
{

	imag = c.imag;
	real = c.real;

}