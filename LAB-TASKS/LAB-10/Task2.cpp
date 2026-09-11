#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    const string targetFile = "notes.txt";
    ifstream inputHandle(targetFile);

    // Verify if the target file can be opened
    if (!inputHandle.is_open()) {
        cerr << "Error: Unable to locate or open '" << targetFile << "'." << endl;
        return 1;
    }

    string currentLine;
    int lineCounter = 0;

    // Traverse the file line by line and increment counter
    while (getline(inputHandle, currentLine)) {
        lineCounter++;
    }

    inputHandle.close();

    cout << "Total number of lines in '" << targetFile << "': " << lineCounter << endl;

    return 0;
}
