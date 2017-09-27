// employee.cpp
// Member function definitions for
#include <iostream>

using std::cout;

#include <cstring>
#include <cassert>
#include "employee.h"

// Constructor dynamically allocates space for the
// first and last name and uses strcpy to copy
// the first and last names into the object.
Employee::Employee( const char *first, const char *last )
{
   firstName = new char[ strlen( first ) + 1 ];
   assert( firstName != 0 );    // test that new worked
   strcpy( firstName, first );

   lastName = new char[ strlen( last ) + 1 ];
   assert( lastName != 0 );     // test that new worked
   strcpy( lastName, last );
}

// Destructor deallocates dynamically allocated memory
Employee::~Employee()
{
   delete [] firstName;
   delete [] lastName;
}

// Return a pointer to the first name
// Const return type prevents caller from modifying private 
// data. Caller should copy returned string before destructor 
// deletes dynamic storage to prevent undefined pointer.
const char *Employee::getFirstName() const 
{ 
   return firstName;   // caller must delete memory
}

// Return a pointer to the last name
// Const return type prevents caller from modifying private 
// data. Caller should copy returned string before destructor 
// deletes dynamic storage to prevent undefined pointer.
const char *Employee::getLastName() const
{
   return lastName;   // caller must delete memory
}

// Print the name of the Employee
void Employee::print() const
   { cout << firstName << ' ' << lastName; }

// Calculate earnings.
double Employee::earnings() const
{
     return 0.0;
}
