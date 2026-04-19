#include <iostream>
using namespace std;

class Person
{
private:
    string name;
    int age;
public:
	Person()
	{
		
	}
    Person(string p_name, int p_age)
    {
        name = p_name;
        age = p_age;
    }
    void input_person() 
	 {
        cout << "Enter name: ";
        cin>>name;
        cout << "Enter age: ";
        cin >> age;
    }
    void display_person()
    {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
    }
     
};

class Employee : public Person
{
private:
    int employee_id;
public:
	Employee()
	{
		
	}
    Employee(string p_name, int p_age, int employeeID) : Person(p_name, p_age)  
    { 
        employee_id = employeeID;
    }
    void input_employee() 
	{
        input_person(); 
        cout << "Enter employee ID: ";
        cin >> employee_id;
    }

    void display_employee()
    {
        display_person();
        cout << "Employee ID: " << employee_id << endl;
    }
};

class Manager : public Employee
{
private:
    string department;
public:
	Manager()
	{
		
	}
    Manager(string p_name, int p_age, int employeeID, string dpt) : Employee(p_name, p_age, employeeID) 
    {
        department = dpt;
    }
     void input_manager() 
	 {
        input_employee(); 
        cout << "Enter department: ";
        cin>>department;
    }

    void display_manager()
    {
        display_employee();
        cout << "Department: " << department << endl;
    }
};

int main()
{
    Manager m;
     cout << "Enter manager details:\n";
	m.input_manager();

    cout << "\nDisplaying manager details:\n";
    m.display_manager();

    return 0;
}