#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <string>
using namespace std;
class Student
{
	//data members
	public:
	string name;
	int roll_no;
	float marks;
	//member functions
	void getData(string a, int b, float c)
	{
		name=a;
		roll_no=b;
		marks=c;
	}
	void Displaydata()
	{
		cout<<"Name: "<<name<<endl;
		cout<<"Roll No: "<<roll_no<<endl;
		cout<<"Marks: "<<marks<<endl;
		
	}
};
#endif