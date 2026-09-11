#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    const string fileName = "notes.txt";

    // 1. Create and write initial lines to file
    ofstream writeStream(fileName);
    if (!writeStream.is_open()) {
        cerr << "Error creating " << fileName << endl;
        return 1;
    }

    writeStream << "Hello World\n";
    writeStream << "This is C++ file handling\n";
    writeStream << "Writing multiple lines\n";
    writeStream.close();

    // 2. Read and display content from file
    cout << "=== Reading File Contents ===" << endl;
    ifstream readStream(fileName);
    if (!readStream.is_open()) {
        cerr << "Error opening " << fileName << " for reading" << endl;
        return 1;
    }

    string fileLine;
    while (getline(readStream, fileLine)) {
        cout << fileLine << endl;
    }
    readStream.close();

    // 3. Append additional text using append mode (ios::app)
    ofstream appendStream(fileName, ios::app);
    if (appendStream.is_open()) {
        appendStream << "Name: Absar, Roll No: 12345\n";
        appendStream.close();
        cout << "\n[Success] Record appended to " << fileName << " successfully." << endl;
    }

    return 0;
}
