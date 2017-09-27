//Use a structure named MovieData to store the information about a movie; create 2 MovieData variables; 
//store value in their members and display in a formatted manner.
//Name: Antonio Borges

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;
const int N = 2;//number of movie recors

struct MovieData
{
    string title;
	string director;
	short year;
	int running_time; /*(in minutes)*/
    
};

int main()
{
    MovieData movieRecord[N];
    
    for(int i=0; i<N;i++)//loop N times
    {
        //prompts user and saves date in the correct struct member	
	cout<<"Insert Movie Data "<<i+1<<": "<<endl;
        cout<<"Title: ";
        cin>>movieRecord[i].title;
        cout<<"Director: ";
        cin>>movieRecord[i].director;
        cout<<"Year Released: ";
        cin>>movieRecord[i].year;
        cout<<"Running time(in minutes): ";
        cin>>movieRecord[i].running_time;
        cout<<endl; 
    } 
    
    cout<<"-------------------------------------"<<endl;
    
    for(int i=0; i <N; i++)
    {
	//prints data for every movie record by accessing the correct member
        cout<<"Movie Data "<<i+1<<": "<<endl;
        cout<<"Title: "<<movieRecord[i].title<<endl; 
        cout<<"Director: "<<movieRecord[i].director<<endl;
        cout<<"Year Released: "<<movieRecord[i].year<<endl;
        cout<<"Running time(in minutes): "<<movieRecord[i].running_time<<endl;
        cout<<endl;
    }
    system("PAUSE");//stops console from exiting
    return 0;
}

