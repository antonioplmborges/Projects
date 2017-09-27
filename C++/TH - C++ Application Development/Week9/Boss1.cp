//  boss1.cpp
// Member function definitions for class Boss
#include <iostream>

using std::cout;

#include "boss1.h"

// Constructor function for class Boss
Boss::Boss( const char *first, const char *last, double s )
   : Employee( first, last )  // call base-class constructor
{ setWeeklySalary( s ); }

// Set the Boss's salary
void Boss::setWeeklySalary( double s )
   { weeklySalary = s > 0 ? s : 0; }

// Get the Boss's pay
double Boss::earnings() const { return weeklySalary; }

// Print the Boss's name 
void Boss::print() const
{
   cout << "\n             Boss: ";
   Employee::print();
}



