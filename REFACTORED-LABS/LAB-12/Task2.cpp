#include <iostream>

using namespace std;

// Class holding measurements in feet and inches
class Distance {
private:
    int feet;
    int inches;

public:
    // Constructor
    Distance(int f, int in) : feet(f), inches(in) {}

    // Friend function declaration allowing access to private feet and inches
    friend void combineDistances(const Distance& d1, const Distance& d2);
};

// Friend function definition
void combineDistances(const Distance& d1, const Distance& d2) {
    int totalFeet = d1.feet + d2.feet;
    int totalInches = d1.inches + d2.inches;

    // Convert excess inches into feet if it reaches 12 or more
    if (totalInches >= 12) {
        totalFeet += totalInches / 12;
        totalInches %= 12;
    }

    cout << "Combined Distance = " << totalFeet << " feet " << totalInches << " inch(es)" << endl;
}

int main() {
    Distance dist1(5, 8);
    Distance dist2(4, 10);

    cout << "--- Adding Distances with Carry-over ---" << endl;
    combineDistances(dist1, dist2);

    return 0;
}
