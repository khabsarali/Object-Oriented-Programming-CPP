#ifndef VOTER_H
#define VOTER_H

#include <iostream>
#include <string>

using namespace std;

// Class representing a citizen voting record
class Voter {
public:
    string citizenName;
    int citizenAge;

    // Read voter details
    void inputData() {
        cout << "Enter your full name: ";
        cin >> citizenName;
        cout << "Enter your age: ";
        cin >> citizenAge;
    }

    // Determine if age meets legal voting threshold (18+)
    bool checkEligibility() {
        return citizenAge >= 18;
    }
};

#endif
