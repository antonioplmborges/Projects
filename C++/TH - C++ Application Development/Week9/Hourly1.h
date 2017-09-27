// hourly1.h
// Definition of class HourlyWorker
#ifndef HOURLY1_H
#define HOURLY1_H
#include "employee.h"

class HourlyWorker : public Employee {
public:
   HourlyWorker( const char *, const char *, 
                 double = 0.0, double = 0.0);
   void setWage( double );
   void setHours( double );
   double earnings() const;
   void print() const;
private:
   double wage;   // wage per hour
   double hours;  // hours worked for week
};

#endif



