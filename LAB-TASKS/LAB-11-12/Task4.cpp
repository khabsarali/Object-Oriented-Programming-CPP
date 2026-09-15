// Lab 11 & 12 - Task 4
// Concept: Static member function + static data member.
// Employee System - the company name is shared by all employees.

#include <iostream>
#include <string>

using namespace std;

class Employee {
private:
    int empId;
    string empName;

    // Static data member: the company is the same for every employee
    static string companyName;

public:
    Employee(int id, string name) : empId(id), empName(name) {}

    void displayEmployee() const {
        cout << "ID: " << empId << " | Name: " << empName
             << " | Company: " << companyName << endl;
    }

    // Static member function: belongs to the class, not to any object.
    // It can only use static members (it has no 'this' pointer).
    static void displayCompanyInfo() {
        cout << "Company Name: " << companyName << endl;
    }
};

// Definition of the static data member outside the class
string Employee::companyName = "Axelytix Technologies";

int main() {
    // Called using the CLASS NAME, without creating any object
    cout << "--- Company Information ---" << endl;
    Employee::displayCompanyInfo();

    Employee e1(101, "Ali");
    Employee e2(102, "Ahmed");
    Employee e3(103, "Hassan");

    cout << "\n--- Employee Records ---" << endl;
    e1.displayEmployee();
    e2.displayEmployee();
    e3.displayEmployee();

    // All three records print the SAME company name, proving it is shared
    cout << "\nThe company name above is stored only once and shared by all objects." << endl;

    return 0;
}
