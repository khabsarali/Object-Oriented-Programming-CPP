#include <iostream>
#include "student.h"
using namespace std;

int main()
{
	Student obj;
	string A;
	int B;
	float C;
	
	cout<<"Enter 1st name: ";
	cin>>A;
	cout<<"Enter roll no: ";
	cin>>B;
	cout<<"Enter marks: ";
	cin>>C;
	obj.getData(A,B,C);
	cout<<"\n";
	obj.Displaydata();

	return 0;
}