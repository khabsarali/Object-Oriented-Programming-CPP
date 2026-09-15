// Lab 11 & 12 - Task 1
// Concept: Friend Function accessing a private data member of a class.

#include <iostream>

using namespace std;

class Box {
private:
    int length; // private: normally unreachable from outside the class

public:
    // Parameterized constructor
    Box(int len) : length(len) {}

    // Friend declaration: this non-member function is allowed to read
    // the private members of Box. It is NOT a member of the class.
    friend void displayLength(const Box& b);
};

// Friend function definition (note: no Box:: prefix, it is a normal function)
void displayLength(const Box& b) {
    // Direct access to the private member 'length' is legal here
    cout << "Length of the Box = " << b.length << " units" << endl;
}

int main() {
    Box b(10);

    // Called like an ordinary function, not as b.displayLength()
    displayLength(b);

    return 0;
}
