// commis1.h
// CommissionWorker class derived from Employee
#ifndef COMMIS1_H
#define COMMIS1_H
#include "employee.h"

class CommissionWorker : public Employee {
public:
   CommissionWorker( const char *, const char *,
                     double = 0.0, double = 0.0,
                     int = 0 );
   void setSalary( double );
   void setCommission( double );
   void setQuantity( int );
   double earnings() const;
   void print() const;
private:
   double salary;       // base salary per week
   double commission;   // amount per item sold
   int quantity;        // total items sold for week
};

#endif



