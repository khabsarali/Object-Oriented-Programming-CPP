#include <iostream>

using namespace std;

// Base class defining common salary computation interface
class Employee {
public:
    virtual double calculateNetSalary() const {
        cout << "[Base] Default employee salary calculation invoked." << endl;
        return 0.0;
    }

    virtual ~Employee() {}
};

// Derived class for permanent salaried staff
class PermanentEmployee : public Employee {
private:
    double monthlyBasic;
    double performanceBonus;

public:
    PermanentEmployee(double basic, double bonus)
        : monthlyBasic(basic), performanceBonus(bonus) {}

    // Overridden method adding base salary and bonus
    double calculateNetSalary() const override {
        return monthlyBasic + performanceBonus;
    }
};

// Derived class for hourly contract staff
class ContractEmployee : public Employee {
private:
    double hourlyRate;
    int hoursBilled;

public:
    ContractEmployee(double rate, int hours)
        : hourlyRate(rate), hoursBilled(hours) {}

    // Overridden method multiplying hourly rate by hours worked
    double calculateNetSalary() const override {
        return hourlyRate * hoursBilled;
    }
};

int main() {
    // Polymorphic pointer array
    Employee* permWorker = new PermanentEmployee(50000.0, 10000.0);
    Employee* contractWorker = new ContractEmployee(500.0, 40);

    cout << "--- Payroll Calculation ---" << endl;
    cout << "Permanent Employee Salary : $" << permWorker->calculateNetSalary() << endl;
    cout << "Contract Employee Salary  : $" << contractWorker->calculateNetSalary() << endl;

    // Clean up heap memory
    delete permWorker;
    delete contractWorker;

    return 0;
}
