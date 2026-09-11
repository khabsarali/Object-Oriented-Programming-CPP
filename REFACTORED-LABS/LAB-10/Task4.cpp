#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    const string databaseFile = "students.txt";

    // Step 1: Write formatted student records to file
    ofstream recordWriter(databaseFile);
    if (!recordWriter.is_open()) {
        cerr << "Error: Unable to open student database for writing." << endl;
        return 1;
    }

    recordWriter << "Absar 101\n";
    recordWriter << "Bilal 102\n";
    recordWriter << "Hassan 103\n";
    recordWriter.close();

    // Step 2: Read records back from the file and format output
    ifstream recordReader(databaseFile);
    if (!recordReader.is_open()) {
        cerr << "Error: Unable to open student database for reading." << endl;
        return 1;
    }

    cout << "=== Enrolled Students Directory ===" << endl;
    cout << "Name\tRoll No" << endl;
    cout << "--------------------" << endl;

    string studentName;
    int rollNumber;

    // Parse structured data token-by-token
    while (recordReader >> studentName >> rollNumber) {
        cout << studentName << "\t" << rollNumber << endl;
    }

    recordReader.close();

    return 0;
}
