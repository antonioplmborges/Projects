#include <iostream.h>

class Time{
public:
	Time() { hour = minute = second = 0; }
	void setTime(int, int, int);
	void printMilitary();
	void printStandard();
private:
	int hour;
	int minute;
	int second;
};
void Time::setTime(int h, int m, int s)
{
	hour = ( h >= 0 && h < 24 ) ? h : 0;
	minute = ( m >= 0 && h < 60 ) ? m : 0;
	second = ( s >= 0 && s < 60 ) ? s : 0;
}
void Time::printMilitary()
{
	cout << (hour < 10 ? "0" : "") << hour << ":"
		<< (minute < 10 ? "0" : "") << minute << endl;
}
void Time::printStandard()
{
	cout << ((hour == 0 || hour == 12) ? 12 : hour % 12)
		<< ":" << (minute < 10 ? "0" : "") << minute
		<< ":" << (second < 10 ? "0" : "") << second
		<< (hour < 12 ? " AM" : " PM") << endl;
}
void main()
{
	Time t;
	cout << "Initial military time is ";
	t.printMilitary();
	cout << "Initial standard time is ";
	t.printStandard();
	t.setTime(13, 30, 5);
	cout << "Military time after setTime is ";
	t.printMilitary();
	cout << "Standard time after setTime is ";
	t.printStandard();
	t.setTime(99,99,99);
	cout << "Invalid time settings. Time is  ";
	t.printMilitary();
}