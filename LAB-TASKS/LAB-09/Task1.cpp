#include <iostream>
using namespace std;
class Employee {
public:
    virtual double calculateSalary() {
        cout << "Base Employee salary calculation called" << endl;
        return 0;
    }
};

class PermanentEmployee : public Employee {
private:
    double basicSalary, bonus;

public:
    PermanentEmployee(double b, double bo) {
        basicSalary = b;
        bonus = bo;
    }

    double calculateSalary() {
        return basicSalary + bonus;
    }
};
class ContractEmployee : public Employee {
private:
    double hourlyRate;
    int hoursWorked;

public:
    ContractEmployee(double r, int h) {
        hourlyRate = r;
        hoursWorked = h;
    }

    double calculateSalary() {
        return hourlyRate * hoursWorked;
    }
};

int main() {
Employee* emp = new   PermanentEmployee(50000, 10000);   
  Employee* emp1 = new  ContractEmployee(500, 40);
    cout << "Permanent Employee Salary: " << emp->calculateSalary() << endl;
    cout << "Contract Employee Salary: " << emp1->calculateSalary() << endl;
    return 0;
}