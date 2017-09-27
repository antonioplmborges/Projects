#include <iostream>
#include "Time.h"

using namespace std;

int main()
{
  cout << "Testing the Time class.\n";

  cout << "Lunch time now: ";
  Time lunch(11,45,00); // Time for lunch
  lunch.show();

  cout << "New lunch hour: ";
  lunch.setHours(12); // Change of lunch hour
  lunch.setMinutes(0);

  lunch.show();
  return 0;
}
