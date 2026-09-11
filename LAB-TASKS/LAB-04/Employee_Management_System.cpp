#include <iostream>
#include <string>

using namespace std;

// Class demonstrating default constructor initialization
class Employee {
private:
    int employeeId;
    string employeeName;
    float monthlySalary;

public:
    // Default constructor providing baseline values
    Employee() {
        employeeId = 0;
        employeeName = "Not_Assigned";
        monthlySalary = 0.0f;
    }

    // Display employee record
    void printEmployeeInfo() {
        cout << "--- Employee Profile ---" << endl;
        cout << "ID     : " << employeeId << endl;
        cout << "Name   : " << employeeName << endl;
        cout << "Salary : $" << monthlySalary << endl;
    }
};

int main() {
    // Instantiate object using default constructor
    Employee emp;

    // Display unassigned default employee record
    emp.printEmployeeInfo();

    return 0;
}
