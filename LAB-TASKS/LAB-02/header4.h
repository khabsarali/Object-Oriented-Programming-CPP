#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#include <iostream>
#include <string>
using namespace std;
class Temperature
{
	//data member
	public:
		int temp_in_celsius,temp_in_farenheit;
	//member function
	void converter()
	{
		cout<<"Enter temperature in Celsius: "<<endl;
		cin>>temp_in_celsius;
		temp_in_farenheit= ((temp_in_celsius)*(9.0/5))+32;
	}
	void display()
	{
		cout<<"Temperature in farenheit is: "<<temp_in_farenheit<<endl;
		
	}
	
};
#endif