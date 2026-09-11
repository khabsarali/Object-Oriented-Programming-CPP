#include <iostream>

using namespace std;

// Class representing physical distance in imperial units
class Distance {
private:
    int feet;
    int inches;

public:
    Distance(int f, int in) : feet(f), inches(in) {}

    // Overloading the equality comparison operator (==)
    bool operator==(const Distance& other) const {
        return (feet == other.feet) && (inches == other.inches);
    }

    // Helper method to compare and print result
    void compareAndPrint(const Distance& other) const {
        if (*this == other) {
            cout << "Comparison Result: Both distance measurements are identical." << endl;
        } else {
            cout << "Comparison Result: Distances are NOT equal." << endl;
        }
    }
};

int main() {
    Distance measurement1(5, 8);
    Distance measurement2(5, 8);
    Distance measurement3(6, 2);

    cout << "--- Comparing Identical Distances ---" << endl;
    measurement1.compareAndPrint(measurement2);

    cout << "\n--- Comparing Different Distances ---" << endl;
    measurement1.compareAndPrint(measurement3);

    return 0;
}
