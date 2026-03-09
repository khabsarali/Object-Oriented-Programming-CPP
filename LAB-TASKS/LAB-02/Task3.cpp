#include <iostream>
#include "voter.h"
using namespace std;

int main()
{
	Voter person;
	if(person.isEligible())
	{
	cout<<"Eligible for vote."<<endl;	
	}
	else
	{
		cout<<"Not eligible for vote."<<endl;
	}
	return 0;
}