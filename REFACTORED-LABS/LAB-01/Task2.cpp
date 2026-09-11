#include <iostream>
#include <string>

using namespace std;

// Structure representing a single student entry
struct StudentRecord {
    string firstName;
    string lastName;
    int rollNumber;
    float marks;

    // Output formatted details of the student
    void showRecord(int index) {
        cout << "\n[Student #" << index << "]" << endl;
        cout << "Full Name   : " << firstName << " " << lastName << endl;
        cout << "Roll Number : " << rollNumber << endl;
        cout << "Marks       : " << marks << endl;
    }
};

int main() {
    int totalCount = 0;

    cout << "Enter the total number of students: ";
    cin >> totalCount;

    if (totalCount <= 0) {
        cout << "Invalid number of students entered." << endl;
        return 1;
    }

    // Allocate an array of student structures dynamically
    StudentRecord* records = new StudentRecord[totalCount];

    // Collect information for each student
    for (int i = 0; i < totalCount; i++) {
        cout << "\n--- Entering details for student " << (i + 1) << " ---" << endl;
        cout << "First Name: ";
        cin >> records[i].firstName;
        cout << "Last Name: ";
        cin >> records[i].lastName;
        cout << "Roll Number: ";
        cin >> records[i].rollNumber;
        cout << "Marks: ";
        cin >> records[i].marks;
    }

    // Display all recorded students
    cout << "\n===============================";
    cout << "\n       STUDENT DIRECTORY       ";
    cout << "\n===============================";

    for (int i = 0; i < totalCount; i++) {
        records[i].showRecord(i + 1);
    }

    // Release dynamically allocated memory
    delete[] records;
    records = nullptr;

    return 0;
}
