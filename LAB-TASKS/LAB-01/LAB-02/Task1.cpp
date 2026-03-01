#include<iostream>
using namespace std;

class student{
	public:
	string name;
	int rollNumber;
	float marks;
	
	void getData(){
		cout<<"Enter Name: ";
		cin>>name;
		cout<<"Enter Roll Number: ";
		cin>>rollNumber;
		cout<<"Enter Marks: ";
		cin>>marks;		
	}
	void displayData(){
	    cout<<"Name: "<<name<<endl;
		cout<<"Roll Number: "<<rollNumber<<endl;	
		cout<<"Marks: "<<marks<<endl;		
	}
};
int main(){
	student s1;
	s1.getData();
	s1.displayData();
	return 0;
}