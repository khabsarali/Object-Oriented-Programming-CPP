#include <iostream>
using namespace std;

struct Student {
    string firstName;
    string lastName;
    int rollNumber;
    float marks;

    void displayStudentInfo() {
        cout << "\nFull Name: " << firstName << " " << lastName << endl;
        cout << "Marks: " << marks << endl;
    }
};

int main() {

    Student *ptr = new Student;   // dynamic memory allocation

    cout << "Enter First Name: ";
    cin >> ptr->firstName;

    cout << "Enter Last Name: ";
    cin >> ptr->lastName;

    cout << "Enter Roll Number: ";
    cin >> ptr->rollNumber;

    cout << "Enter Marks: ";
    cin >> ptr->marks;

    // Call function using pointer
    ptr->displayStudentInfo();

    delete ptr;   // free memory

    return 0;
}