/*
/Homework1
/Name:Antonio Borges
/Program:Compare string and substring using string class
*/

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;
const int CAPACITY = 10;

int main()
{
    string input;
    string people [CAPACITY] = {
        "Becky Warren, 555-1223",
        "Joe Looney, 555-0097",
        "Gerri Palmer, 555-8787",
        "Lynn Presnell, 555-1212",
        "Holly Gaddis, 555-8878",
        "Sam Wiggins, 555-0998",
        "Bob Kain, 555-8712",
        "Tim Haynes, 555-7676",
        "Warren Gaddis, 555-9037",
        "Ron Palmer, 777-2783"
    };
    
    cout<<"Enter a name or partial name: "<<endl;
    cin>>input;
    
    for(int i=0; i < CAPACITY; i++)// sizeof(people)/sizeof(people[0]) - number of elements in the array
    {
       int found = people[i].find(input); 
       if(found!= -1){
           int result = people[i].compare(found, input.length(), input); // or people[i].compare(found, input.length(), input,0, input.length())
                      
           if(result==0)             
               //if(strstr(people[i].c_str(), input.c_str())) from the cstring ...possible solution
               cout<<people[i]<<endl;
        }
    };
    system("pause");
    return 0;
}
