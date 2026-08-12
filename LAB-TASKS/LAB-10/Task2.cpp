#include <iostream>
#include <fstream>
using namespace std;

int main() {

    ifstream file("notes.txt");

    string line;
    int count = 0;

    while (getline(file, line)) {
        count++;
    }

    file.close();

    cout << "Total number of lines in file: " << count << endl;

    return 0;
}