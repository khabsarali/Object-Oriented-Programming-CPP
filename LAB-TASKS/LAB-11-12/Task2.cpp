// Lab 11 & 12 - Task 2
// Concept: Friend function that takes two objects as parameters and
// performs a mathematical operation on their private data.

#include <iostream>

using namespace std;

class Distance {
private:
    int feet;
    int inches;

public:
    // Constructor
    Distance(int f, int in) : feet(f), inches(in) {}

    // Display helper (normal member function)
    void show() const {
        cout << feet << " feet " << inches << " inches" << endl;
    }

    // Friend function can read the private feet/inches of BOTH objects
    friend void addDistance(const Distance& d1, const Distance& d2);
};

// Friend function definition
void addDistance(const Distance& d1, const Distance& d2) {
    int totalFeet = d1.feet + d2.feet;
    int totalInches = d1.inches + d2.inches;

    // 12 inches make 1 foot, so carry the extra inches over
    if (totalInches >= 12) {
        totalFeet += totalInches / 12;
        totalInches = totalInches % 12;
    }

    cout << "Total Distance = " << totalFeet << " feet " << totalInches << " inches" << endl;
}

int main() {
    Distance d1(5, 8);
    Distance d2(3, 7);

    cout << "First Distance  : ";
    d1.show();
    cout << "Second Distance : ";
    d2.show();

    addDistance(d1, d2);

    return 0;
}
