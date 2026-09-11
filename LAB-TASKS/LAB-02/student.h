#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

using namespace std;

// Class to manage individual student data
class Student {
public:
    string fullName;
    int rollNumber;
    float marks;

    // Method to assign student attributes
    void setDetails(string name, int roll, float obtMarks) {
        fullName = name;
        rollNumber = roll;
        marks = obtMarks;
    }

    // Method to display student attributes
    void printDetails() {
        cout << "Name        : " << fullName << endl;
        cout << "Roll Number : " << rollNumber << endl;
        cout << "Marks       : " << marks << endl;
    }
};

#endif
