#include <iostream>
#include <string>

using namespace std;

// Structure to hold basic student details
struct Student {
    string firstName;
    string lastName;
    int rollNumber;
    float marks;

    // Member function to print the stored student record
    void printDetails() {
        cout << "--- Student Information ---" << endl;
        cout << "Name: " << firstName << " " << lastName << endl;
        cout << "Roll Number: " << rollNumber << endl;
        cout << "Marks: " << marks << endl;
    }
};

int main() {
    // Create an instance of Student
    Student s;

    // Populate data members directly
    s.firstName = "Absar";
    s.lastName = "Ali";
    s.rollNumber = 31;
    s.marks = 80.0f;

    // Display the student's information
    s.printDetails();

    return 0;
}
