#include <iostream>
using namespace std;

// Base class
class Person
{
	private:
		string name;
		int age;

	public:
		// Constructor
		Person(string p_name, int p_age)
		{
			name = p_name;
			age = p_age;
		}

		
		void display_person_info()
		{
			cout << "Name: " << name << endl;
			cout << "Age: " << age << endl;
		}
};

// Derived class
class Student : public Person
{
	private:
		int student_ID;

	public:
		// Constructor
		Student(string name, int age, int id) : Person(name, age)
		{
			student_ID = id;
		}

		
		void display_student_info()
		{
			display_person_info();   
			cout << "Student ID: " << student_ID << endl;
		}
};

int main()
{
	string P_name;
	int P_age, P_id;

	cout << "Enter name: ";
	cin >> P_name;

	cout << "Enter age: ";
	cin >> P_age;

	cout << "Enter student ID: ";
	cin >> P_id;

	Student s1(P_name, P_age, P_id);

	cout << "\n--- Student Information ---\n";


	s1.display_person_info();     
	s1.display_student_info();     

	return 0;
}