// Homework 1: Create a class CounterType that increments and decrements counter and implement it in the main function.
//Name: Antonio Borges

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

class CounterType
{
private:
	int counter;

public:
	CounterType();//Constructor
	CounterType(int);//Constructor with 1 parameter
	//Member functions
	void incrementCounter(int);//increments counter by 1
	void decrementCounter(int);//decrementes counter by 1
	int getCounter() const;// returns counter value
	void outputCounter(ostream&);//outputs the counter value for the user to see



};//end of class declaration

CounterType::CounterType()
{
	counter = 0;
}


CounterType::CounterType(int c)
{
	counter = c;
}

void CounterType::incrementCounter(int c)
{
	counter = c + 1;
	if (counter<0)
	{
		cout << "***Negative counter***" << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
}

void CounterType::decrementCounter(int c)
{
	counter = c - 1;
	if (counter<0)
	{
		cout << "***Negative counter***" << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
}


int CounterType::getCounter() const
{
	return counter;
}

void CounterType::outputCounter(ostream& output)
{
	output << counter << endl;
}


;
int main()
{
	CounterType counterApp;//constructor initialized with 0
	int counterVar = 5;
	int counterVar2 = 10;
	CounterType counterApp2(counterVar2);//constructor initialized with 10

	counterApp.outputCounter(cout);//output '0'
	counterApp2.outputCounter(cout);//output '10'

	cout << "Increment 3 times" << endl;
	counterApp.incrementCounter(counterVar);//now counter is equal to counterVar = 5
	counterApp.incrementCounter(counterApp.getCounter());
	counterApp.incrementCounter(counterApp.getCounter());//counter = 8

	counterApp2.incrementCounter(counterApp2.getCounter());
	counterApp2.incrementCounter(counterApp2.getCounter());
	counterApp2.incrementCounter(counterApp2.getCounter());//counter = 13

	counterApp.outputCounter(cout);//output '8'
	counterApp2.outputCounter(cout);//output '13'

	counterApp.decrementCounter(counterApp.getCounter());
	counterApp.decrementCounter(counterApp.getCounter());//counter = 6

	counterApp2.decrementCounter(counterApp2.getCounter());
	counterApp2.decrementCounter(counterApp2.getCounter());//counter = 11

	cout << counterApp.getCounter() << endl;//output '6'
	cout << counterApp2.getCounter() << endl;//output '11'

	system("pause");
	return 0;
}

