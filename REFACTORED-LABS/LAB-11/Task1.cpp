#include <iostream>

using namespace std;

// Forward declaration / Class definition
class Box {
private:
    int length;

public:
    // Parameterized constructor
    Box(int len) : length(len) {}

    // Friend function declaration granting non-member access to private members
    friend void showBoxLength(const Box& b);
};

// Non-member friend function definition
void showBoxLength(const Box& b) {
    // Directly accessing private member 'length'
    cout << "Box Dimension (Length) = " << b.length << " units" << endl;
}

int main() {
    // Instantiate Box object
    Box sampleBox(15);

    // Call friend function like a standard non-member function
    showBoxLength(sampleBox);

    return 0;
}
