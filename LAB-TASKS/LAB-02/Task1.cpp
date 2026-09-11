#include <iostream>
#include "student.h"

using namespace std;

int main() {
    Student studentObj;
    string inputName;
    int inputRoll;
    float inputMarks;

    // Collect student information from the console
    cout << "Enter student name: ";
    cin >> inputName;

    cout << "Enter roll number: ";
    cin >> inputRoll;

    cout << "Enter marks: ";
    cin >> inputMarks;

    // Pass data to the object method
    studentObj.setDetails(inputName, inputRoll, inputMarks);

    cout << "\n--- Student Summary ---" << endl;
    studentObj.printDetails();

    return 0;
}
