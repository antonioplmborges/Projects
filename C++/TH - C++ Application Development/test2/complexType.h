//#include "stdafx.h"
#include <iostream>

class complexType
{
private:
	int real, imag;//real and imaginary part
	
public:
	//Constructor
	complexType();
	complexType(int, int);
	//Operator overload
	complexType operator+(const complexType&);
	complexType operator*(const complexType&);
	void operator=(const complexType &);
	bool operator==(const complexType&);
	friend std::ostream& operator<<(std::ostream&,const complexType&);
	friend std::istream& operator>>(std::istream&, complexType&);
};