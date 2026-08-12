#include <iostream>
#include <fstream>
using namespace std;

int main() {

    // Step 1: Create and write to source file
    ofstream source("source.txt");
    source << "Hello World\n";
    source << "This is the source file\n";
    source << "We are copying this content\n";
    source.close();

    // Step 2: Open source file for reading
    ifstream readSource("source.txt");

    // Step 3: Create destination file
    ofstream dest("destination.txt");

    string line;

    // Step 4: Copy content line by line
    while (getline(readSource, line)) {
        dest << line << endl;
    }

    readSource.close();
    dest.close();

    cout << "Content copied successfully from source.txt to destination.txt" << endl;

    return 0;
}