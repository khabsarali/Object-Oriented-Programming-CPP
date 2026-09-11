#include <iostream>
#include <string>

using namespace std;

// Structure definition for individual student profile
struct StudentProfile {
    string firstName;
    string lastName;
    int rollNumber;
    float marks;

    // Display student profile data
    void displayInfo() {
        cout << "\n--- Student Profile Output ---" << endl;
        cout << "Name        : " << firstName << " " << lastName << endl;
        cout << "Roll Number : " << rollNumber << endl;
        cout << "Marks       : " << marks << endl;
    }
};

int main() {
    // Dynamically allocate memory for a StudentProfile on the heap
    StudentProfile* studentPtr = new StudentProfile;

    // Take user input using the arrow (->) member access operator
    cout << "Enter student's first name: ";
    cin >> studentPtr->firstName;

    cout << "Enter student's last name: ";
    cin >> studentPtr->lastName;

    cout << "Enter roll number: ";
    cin >> studentPtr->rollNumber;

    cout << "Enter obtained marks: ";
    cin >> studentPtr->marks;

    // Call member function through the pointer
    studentPtr->displayInfo();

    // Free heap memory to prevent memory leaks
    delete studentPtr;
    studentPtr = nullptr;

    return 0;
}
