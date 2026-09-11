#include <iostream>
#include "voter.h"

using namespace std;

int main() {
    Voter applicant;

    // Collect name and age
    applicant.inputData();

    // Verify voting eligibility
    if (applicant.checkEligibility()) {
        cout << "\nStatus: Eligible to vote." << endl;
    } else {
        cout << "\nStatus: Not eligible to vote (must be 18 or older)." << endl;
    }

    return 0;
}
