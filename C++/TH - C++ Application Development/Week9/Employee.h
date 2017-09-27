// employee.h
// Abstract base class Employee
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Employee {
public:
   Employee( const char *, const char * );
   ~Employee();   // destructor reclaims memory
   const char *getFirstName() const;
   const char *getLastName() const;
   double earnings() const;
   void print() const;        
private:
   char *firstName;
   char *lastName;
};

#endif


