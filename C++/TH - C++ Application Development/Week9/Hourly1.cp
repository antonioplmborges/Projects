//hourly1.cpp
// Member function definitions for class HourlyWorker
#include <iostream>

using std::cout;

#include "hourly1.h"

// Constructor for class HourlyWorker
HourlyWorker::HourlyWorker( const char *first, 
                            const char *last,
                            double w, double h )
   : Employee( first, last )   // call base-class constructor
{
   setWage( w );
   setHours( h );
}

// Set the wage
void HourlyWorker::setWage( double w ) 
   { wage = w > 0 ? w : 0; }

// Set the hours worked
void HourlyWorker::setHours( double h )
   { hours = h >= 0 && h < 168 ? h : 0; }

// Get the HourlyWorker's pay
double HourlyWorker::earnings() const 
{ 
   if ( hours <= 40 ) // no overtime
      return wage * hours;
   else               // overtime is paid at wage * 1.5
      return 40 * wage + ( hours - 40 ) * wage * 1.5;
}

// Print the HourlyWorker's name 
void HourlyWorker::print() const
{
   cout << "\n    Hourly worker: ";
   Employee::print();
}


