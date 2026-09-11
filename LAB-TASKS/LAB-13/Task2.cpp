#include <iostream>

using namespace std;

// Generic function template returning the smaller of two values
template <typename T>
T getMinimum(T val1, T val2) {
    return (val1 < val2) ? val1 : val2;
}

int main() {
    int int1, int2;
    double dbl1, dbl2;
    char char1, char2;

    // Integer comparison
    cout << "Enter two integers: ";
    cin >> int1 >> int2;
    cout << "Minimum integer: " << getMinimum(int1, int2) << endl;

    // Floating-point comparison
    cout << "\nEnter two floating-point numbers: ";
    cin >> dbl1 >> dbl2;
    cout << "Minimum floating-point value: " << getMinimum(dbl1, dbl2) << endl;

    // Character comparison
    cout << "\nEnter two characters: ";
    cin >> char1 >> char2;
    cout << "Minimum character (lexicographical): " << getMinimum(char1, char2) << endl;

    return 0;
}
