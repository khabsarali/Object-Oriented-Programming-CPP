#include <iostream>
#include <string>

using namespace std;

// Function template to output any given value twice
template <typename T>
void outputTwice(T value) {
    cout << value << endl;
    cout << value << endl;
}

int main() {
    cout << "--- Integer Test ---" << endl;
    outputTwice(5);

    cout << "\n--- Floating Point Test ---" << endl;
    outputTwice(3.14);

    cout << "\n--- String Test ---" << endl;
    outputTwice(string("Hello"));

    return 0;
}
