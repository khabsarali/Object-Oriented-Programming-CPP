#include <iostream>
#include <string>

using namespace std;

// Base class representing a general person
class Person {
private:
    string personName;
    int personAge;

public:
    // Base constructor
    Person(string name, int age) : personName(name), personAge(age) {}

    // Method to display base person attributes
    void displayPersonDetails() const {
        cout << "Name : " << personName << endl;
        cout << "Age  : " << personAge << " years" << endl;
    }
};

// Derived class demonstrating Single Inheritance (Person -> Student)
class Student : public Person {
private:
    int studentId;

public:
    // Derived constructor calling base class constructor
    Student(string name, int age, int id) : Person(name, age), studentId(id) {}

    // Method to display full student profile
    void displayStudentDetails() const {
        displayPersonDetails(); // Call parent display method
        cout << "ID   : " << studentId << endl;
    }
};

int main() {
    string nameInput;
    int ageInput, idInput;

    cout << "Enter student name: ";
    cin >> nameInput;

    cout << "Enter student age: ";
    cin >> ageInput;

    cout << "Enter student ID: ";
    cin >> idInput;

    // Instantiate derived object
    Student s(nameInput, ageInput, idInput);

    cout << "\n--- Base Information ---" << endl;
    s.displayPersonDetails();

    cout << "\n--- Complete Student Record ---" << endl;
    s.displayStudentDetails();

    return 0;
}
