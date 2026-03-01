#include <iostream>
using namespace std;
//Declare Struct
struct student{
	string first_name , last_name;
	int roll_number;
	float marks;
//Display Info
	void diplaystudent()
	    {
        cout << "Student Name: " << first_name << " " << last_name << endl;
        cout << "Roll Number: " << roll_number << endl;
        cout << "Marks: " << marks << endl;
    }
} s1;
int main()
{
// Assign values to data members
s1.first_name="Absar";
s1.last_name="Ali";
s1.roll_number=31;
s1.marks=80;
s1.diplaystudent();
return 0;
}


