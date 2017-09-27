//Use a structure to store the weather data for a every month and do operations with the data.
//Name: Antonio Borges

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

//constansts
const int MONTHS = 12;
const int MIN_TEMPERATURE = -100;
const int MAX_TEMPERATURE = 140;


struct WeatherData
{
	int total_rainfall;
	int high_temperature;
	int low_temperature;
	int average_temperature;
};

int main()
{
	WeatherData weatherRecord[MONTHS];

	
	string months[]={
		"January", "February", "March", "April", "May", "June", "July", "August", "September","October", "November", "December"
	};//uses string index to print a specific month	

	for(int i=0; i< MONTHS;i++)//loops 12x -  1 for every month
	{
		cout<<months[i]<<endl;//prints the month in question
		cout<<"Enter total rainfal: ";
		cin>>weatherRecord[i].total_rainfall;
		cout<<"Enter highest temperature: ";
		cin>>weatherRecord[i].high_temperature;
		//input validation
		while(weatherRecord[i].high_temperature<MIN_TEMPERATURE || weatherRecord[i].high_temperature>MAX_TEMPERATURE)
		{
			cout<<"***Out of range temperature***"<<endl;
			cout<<"Enter highest temperature: ";
			cin>>weatherRecord[i].high_temperature;//prompts the user again
		}
		cout<<"Enter lowest temperature: ";
		cin>>weatherRecord[i].low_temperature;
		//input validation
		while(weatherRecord[i].low_temperature<MIN_TEMPERATURE || weatherRecord[i].low_temperature>MAX_TEMPERATURE)
		{
			cout<<"***Out of range temperature***"<<endl;
			cout<<"Enter lowest temperature: ";
			cin>>weatherRecord[i].low_temperature;//prompts the user again
		}
		cout<<"Enter average temperature temperature: ";
		cin>>weatherRecord[i].average_temperature;
		while(weatherRecord[i].average_temperature<MIN_TEMPERATURE && weatherRecord[i].average_temperature>MAX_TEMPERATURE)
		{
			cout<<"***Out of range temperature***"<<endl;
			cout<<"Enter average temperature: ";
			cin>>weatherRecord[i].average_temperature;
		}
		cout<<endl;
			
	}

	int total_monthly_fall = 0;
	int total_monthly_avg_temp = 0;
	int highest_temp = weatherRecord[0].high_temperature;
	int lowest_temp = weatherRecord[0].high_temperature;

	for(int i=0;i<MONTHS;i++)
		total_monthly_fall+= weatherRecord[i].total_rainfall;//adds the total monthly fall for the year 

	for(int i=0;i<MONTHS;i++)
		total_monthly_avg_temp+= weatherRecord[i].average_temperature;//adds the total monthly average temperature for the year
		
	for(int i=0;i<(MONTHS-1);i++)
	{//compares highest temperature and returns the maximum.
	   if(weatherRecord[i+1].high_temperature>highest_temp)
	       highest_temp = weatherRecord[i+1].high_temperature;
    }  
    for(int i=0;i<(MONTHS-1);i++)
	{//compares lowest temperature and returns the minimum.
	   if(weatherRecord[i+1].low_temperature<lowest_temp)
	       lowest_temp = weatherRecord[i+1].low_temperature;
    }  
	   
    cout<<"-----------------------------------------------------------------------------"<<endl;
	cout<<"Average monthly fall: ";
	cout<<total_monthly_fall/MONTHS<<endl;//divides the total monthly by 12 to find the average
	cout<<"Total rainfal for the year: ";
	cout<<total_monthly_fall<<endl;
	cout<<"Highest temperature of the year: ";
	cout<<highest_temp<<endl;
	cout<<"Lowest temperature of the year ";
	cout<<lowest_temp<<endl ;
	cout<<"Average of all the monthly average temperatures: ";
	cout<<total_monthly_avg_temp/MONTHS<<endl;

	system("pause");//stops console from exiting
	return 0;
}

