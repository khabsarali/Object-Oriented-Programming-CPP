#include <iostream>
#include <string>

using namespace std;

// Base class representing a general employee
class Employee {
private:
    string empName;
    int salary;

public:
    Employee() : empName(""), salary(0) {}

    Employee(string name, int sal) : empName(name), salary(sal) {}

    // Input basic employee info
    void readEmployeeInfo() {
        cout << "Enter employee name: ";
        cin >> empName;
        cout << "Enter monthly salary: ";
        cin >> salary;
    }

    // Display basic employee info
    void showEmployeeInfo() const {
        cout << "Name   : " << empName << endl;
        cout << "Salary : $" << salary << endl;
    }
};

// Derived class 1: Developer inheriting from Employee
class Developer : public Employee {
private:
    string primaryLanguage;

public:
    Developer() : Employee(), primaryLanguage("") {}

    void readDeveloperInfo() {
        readEmployeeInfo();
        cout << "Enter primary programming language: ";
        cin >> primaryLanguage;
    }

    void showDeveloperProfile() const {
        showEmployeeInfo();
        cout << "Role   : Developer (" << primaryLanguage << ")" << endl;
    }
};

// Derived class 2: Designer inheriting from Employee
class Designer : public Employee {
private:
    string designTool;

public:
    Designer() : Employee(), designTool("") {}

    void readDesignerInfo() {
        readEmployeeInfo();
        cout << "Enter primary design tool: ";
        cin >> designTool;
    }

    void showDesignerProfile() const {
        showEmployeeInfo();
        cout << "Role   : Designer (" << designTool << ")" << endl;
    }
};

int main() {
    cout << "=== Developer Entry ===" << endl;
    Developer dev;
    dev.readDeveloperInfo();

    cout << "\n=== Designer Entry ===" << endl;
    Designer des;
    des.readDesignerInfo();

    cout << "\n==============================";
    cout << "\n       STAFF DIRECTORY        ";
    cout << "\n==============================" << endl;

    cout << "\n[Developer Details]" << endl;
    dev.showDeveloperProfile();

    cout << "\n[Designer Details]" << endl;
    des.showDesignerProfile();

    return 0;
}
