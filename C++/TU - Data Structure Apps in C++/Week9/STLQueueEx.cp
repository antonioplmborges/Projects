// Demonstrate the queue library usage in standard template library (STL)

#include <iostream>
#include <queue>
using namespace std;

int main()
{
   queue<int> q;
   q.push(100);
   q.push(200);
   q.push(300);
   q.push(400);

   cout << "Size of the queue: " << q.size() << endl;

   cout << q.front() << endl;
   q.pop();

   cout << q.front() << endl;
   q.pop();

   cout << q.front() << endl;
   q.pop();

   cout << q.front() << endl;
   q.pop();

   if ( q.empty() ) {
   cout << "Queue is empty" << endl;
   }
}
/*
OUTPUT:- 
Size of the queue: 4
100
200
300
400
Queue is empty
*/
