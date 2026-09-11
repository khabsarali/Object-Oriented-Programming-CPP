#include <iostream>
#include <string>

using namespace std;

// Base class in multilevel hierarchy
class Person {
private:
    string personName;
    int personAge;

public:
    Person() : personName(""), personAge(0) {}

    Person(string name, int age) : personName(name), personAge(age) {}

    void inputPerson() {
        cout << "Enter name: ";
        cin >> personName;
        cout << "Enter age: ";
        cin >> personAge;
    }

    void displayPerson() const {
        cout << "Name : " << personName << endl;
        cout << "Age  : " << personAge << " years" << endl;
    }
};

// Intermediate derived class inheriting from Person
class Employee : public Person {
private:
    int employeeId;

public:
    Employee() : Person(), employeeId(0) {}

    Employee(string name, int age, int id) : Person(name, age), employeeId(id) {}

    void inputEmployee() {
        inputPerson();
        cout << "Enter employee ID: ";
        cin >> employeeId;
    }

    void displayEmployee() const {
        displayPerson();
        cout << "ID   : " << employeeId << endl;
    }
};

// Final derived class inheriting from Employee
class Manager : public Employee {
private:
    string assignedDepartment;

public:
    Manager() : Employee(), assignedDepartment("") {}

    Manager(string name, int age, int id, string dept)
        : Employee(name, age, id), assignedDepartment(dept) {}

    void inputManager() {
        inputEmployee();
        cout << "Enter department: ";
        cin >> assignedDepartment;
    }

    void displayManager() const {
        displayEmployee();
        cout << "Dept : " << assignedDepartment << endl;
    }
};

int main() {
    Manager mgr;

    cout << "=== Enter Manager Details ===" << endl;
    mgr.inputManager();

    cout << "\n=== Manager Profile Summary ===" << endl;
    mgr.displayManager();

    return 0;
}
