#ifndef VOTER_H
#define VOTER_H
#include <iostream>
#include <string>
using namespace std;
//class
class Voter
	{
		//data members
		public:
		string name;
		int age;
		//member functions
		bool isEligible();
	};
bool Voter::isEligible()
{
	cout<<"Enter Your name: "<<endl;
	cin>>name;
	cout<<"Enter your age: "<<endl;
	cin>>age;
	if(age>=18)
	{
//		cout<<"Eligible for vote."<<endl;
		return true;
	}
	else
	{
//		cout<<"Not eligible for vote."<<endl;
		return false;
	}
}
#endif