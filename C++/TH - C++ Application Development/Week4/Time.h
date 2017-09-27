#include <iostream>

using namespace std;

// Define a class called Time, to represent time in a program.

class Time
{
   public:		// Behavior (or interface)
	Time();		// default constructor
	Time(int, int, int);	// 3-argument constructor
	int getHours();	// "get" (accessor) methods
	int getMinutes();
	int getSeconds();
	void setHours(int);	// "set" (mutator) methods
	void setMinutes(int);
	void setSeconds(int);
	void show();
   private:		// Attributes (properties) of Time
	int hours;
	int minutes;
	int seconds;
};

// Implement the methods (or functions)

// The Constructors
Time::Time()	// Default constructor
{
	hours = 0;
	minutes = 0;
	seconds= 0;
}
Time::Time (int h, int m, int s) // Constructor with 3 args
{
  setHours(h);
  setMinutes(m);
  setSeconds(s);
}

// Accessor or getter methods
int Time::getHours()
{
	return hours;
}
int Time::getMinutes()
{
	return minutes;
}
int Time::getSeconds()
{
	return seconds;
}

// Mutator or setter methods
void Time::setHours(int h)
{
  if (h >= 0 && h < 24)
	hours = h;
  else 
    hours = 0;
}
void Time::setMinutes(int m)
{
  if (m >= 0 && m < 60)
	minutes = m;
  else
    minutes = 0;
}
void Time::setSeconds(int s)
{
  if (s >= 0 && s < 60)
	seconds = s;
  else
    seconds = 0;
}

void Time::show()
{
	cout << hours << ":" << minutes << ":" << seconds << endl;
}
