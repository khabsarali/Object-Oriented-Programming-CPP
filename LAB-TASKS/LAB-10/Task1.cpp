#include <iostream>
#include <fstream>
using namespace std;

int main() {

    // 1. Create & Write to file
    ofstream writeFile("notes.txt"); // creates file
    writeFile << "Hello World\n";
    writeFile << "This is C++ file handling\n";
    writeFile << "Writing multiple lines\n";
    writeFile.close();

    // 2. Read file
    cout << "File Contents:\n";
    ifstream readFile("notes.txt");
    string line;

    while (getline(readFile, line)) {
        cout << line << endl;
    }
    readFile.close();

    // 3. Append to file
    ofstream appendFile("notes.txt", ios::app);
    appendFile << "Name: Absar, Roll No: 12345\n";
    appendFile.close();

    return 0;
}