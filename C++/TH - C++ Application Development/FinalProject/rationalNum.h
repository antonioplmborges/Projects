#include <iostream>

class rationalNum
{
private:
	int numerator;
	int denominator;

public:
	//Constructor
	rationalNum();
	rationalNum(int, int);
	rationalNum(int);
	//Member function
	void normalize();
	//Operator overload
	rationalNum operator+(const rationalNum&);
	rationalNum operator-(const rationalNum&);
	rationalNum operator*(const rationalNum&);
	rationalNum operator/(const rationalNum&);
	void operator=(const rationalNum&);
	bool operator==(const rationalNum&) const;
	bool operator>(rationalNum&);
	bool operator<(rationalNum&);
	friend std::ostream& operator<<(std::ostream&, const rationalNum&);
	friend std::istream& operator>>(std::istream&, rationalNum&);

};