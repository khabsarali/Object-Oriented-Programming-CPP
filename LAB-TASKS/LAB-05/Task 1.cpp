#include <iostream>
using namespace std;

class Employee
{
	private:
		string name;
		int salary;
	public:
		Employee()
		{
			
		}
		Employee(string e_name, int e_salary)
		{
			name=e_name;
			salary=e_salary;
		}
		 void input_employee()
		{
        cout << "Enter employee name: ";
        cin>>name;
        cout << "Enter salary: ";
        cin >> salary;
    	}
    	void display_employee()
	{
        cout << "Name: " << name << endl;
        cout << "Salary: " << salary << endl;
    }

		
};

class Developer : public Employee
{
private:
    string programming_language;
public:
    Developer() {}

    void input_developer() 
	{
        input_employee();
        cout << "Enter programming language: ";
        cin>>programming_language;
    }
void display_developer() 
	{
        display_employee();  
        cout << "Programming Language: " << programming_language << endl;
    }

};
class Designer : public Employee
 {
private:
    string design_tool;
public:
    Designer() {}

    void input_designer()
	 {
        input_employee();  
        cout << "Enter design tool: ";
       cin>>design_tool;
    }

    void display_designer()
	{
        display_employee();  
        cout << "Design Tool: " << design_tool << endl;
    }
};

int main() 
{
    cout << "Enter details for Developer:\n";
    Developer dev;
    dev.input_developer();

    cout << "\nEnter details for Designer:\n";
    Designer des;
    des.input_designer();

    cout << "\nDisplaying Developer Details:\n";
    dev.display_developer();

    cout << "\nDisplaying Designer Details:\n";
    des.display_designer();

    return 0;
}