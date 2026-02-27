#include <iostream>
using namespace std;

struct Student {
    string firstName;
    string lastName;
    int rollNumber;
    float marks;

    void displayStudentInfo() {
        cout << "Full Name: " << firstName << " " << lastName << endl;
        cout << "Roll Number: " << rollNumber << endl;
        cout << "Marks: " << marks << endl;
        cout << "-------------------------" << endl;
    }
};

int main() {
    int choice;

    cout << "=== Student Management Program ===\n";
    cout << "1. Enter multiple students (array of structures)\n";
    cout << "2. Enter single student (pointer to structure)\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        // Array of structures
        int n;
        cout << "\nEnter number of students: ";
        cin >> n;

        Student students[n];  // Array

        for (int i = 0; i < n; i++) {
            cout << "\nEnter details for Student " << i + 1 << endl;
            cout << "First Name: ";
            cin >> students[i].firstName;
            cout << "Last Name: ";
            cin >> students[i].lastName;
            cout << "Roll Number: ";
            cin >> students[i].rollNumber;
            cout << "Marks: ";
            cin >> students[i].marks;
        }

        cout << "\n--- Student Information ---\n";
        for (int i = 0; i < n; i++) {
            students[i].displayStudentInfo();
        }

    } else if (choice == 2) {
        // Pointer to structure
        Student *ptr = new Student;

        cout << "\nEnter details for the student:\n";
        cout << "First Name: ";
        cin >> ptr->firstName;
        cout << "Last Name: ";
        cin >> ptr->lastName;
        cout << "Roll Number: ";
        cin >> ptr->rollNumber;
        cout << "Marks: ";
        cin >> ptr->marks;

        cout << "\n--- Student Information ---\n";
        ptr->displayStudentInfo();

        delete ptr;  // Free memory

    } else {
        cout << "Invalid choice!\n";
    }

    return 0;
}