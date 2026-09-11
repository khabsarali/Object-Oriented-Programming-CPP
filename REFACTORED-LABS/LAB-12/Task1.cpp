#include <iostream>

using namespace std;

// Class holding private length measurement
class Box {
private:
    int boxLength;

public:
    Box(int len) : boxLength(len) {}

    // Friend function prototype
    friend void printDimension(const Box& b);
};

// Friend function accessing private data member directly
void printDimension(const Box& b) {
    cout << "Measured Length = " << b.boxLength << endl;
}

int main() {
    Box b1(15);

    // Invoke friend function
    printDimension(b1);

    return 0;
}
