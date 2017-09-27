//  boss1.h
// Boss class derived from Employee
#ifndef BOSS1_H
#define BOSS1_H
#include "employee.h"

class Boss : public Employee {
public:
   Boss( const char *, const char *, double = 0.0 );
   void setWeeklySalary( double );
   double earnings() const;
   void print() const;
private:
   double weeklySalary; 
};

#endif



