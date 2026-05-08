#include<iostream>
using namespace std;
class employee
{
	private:
		int ID;
		string name;
		float salary;
	public:
		employee()
		{
			ID=0;
			name="Not_Assigned";
			salary=0.0;
		}
	void displayDetails()
	{
		cout<<"ID: "<<ID<<endl;
		cout<<"Name: "<<name<<endl;
		cout<<"Salary: "<<salary<<endl;
	}
};

int main()
{
	employee e1;
	e1.displayDetails();
	return 0;
}