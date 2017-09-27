// Use a queue of strings to insert three string objects on the queue.
//The string objects are initialized with the strings “These  “, “are  “, “more than   “. 
//Read and print two elements from the queue. 
//Next, insert two new elements, initialized with the strings “Four   “, “words!  “, on the queue.  
//Skip (pop) one element. Then read and print two elements.  Finally, print number of elements in the queue.
//Name:Antonio Borges

#include "stdafx.h"
#include <algorithm>
#include <queue>
#include <string>
#include <iostream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	queue <string> q;
	q.push("These ");
	q.push("are ");
	q.push("more than ");

	cout  << q.front();
	q.pop();

	cout << q.front();
	q.pop();

	q.push("Four ");
	q.push("words ");	

	q.pop();
	cout << q.front();
	q.pop();

	cout << q.front();
	q.pop();

	while(!q.empty()) 
		q.pop();
	
		
	cout << "\nNumber of elements in Q: "<< q.size() << endl;

	system("pause");
	return 0;
}

