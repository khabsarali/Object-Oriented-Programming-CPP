#include <iostream>
#include <string>

using namespace std;

// Class demonstrating parameterized constructor initialization
class BankAccount {
private:
    string accountNumber;
    string accountHolder;
    double currentBalance;

public:
    // Parameterized constructor initializing account attributes
    BankAccount(string accNum, string holderName, double initialDeposit) {
        accountNumber = accNum;
        accountHolder = holderName;
        currentBalance = initialDeposit;
    }

    // Display bank account information
    void displayAccountSummary() {
        cout << "--- Bank Account Summary ---" << endl;
        cout << "Account Number : " << accountNumber << endl;
        cout << "Account Holder : " << accountHolder << endl;
        cout << "Balance        : $" << currentBalance << endl;
    }
};

int main() {
    // Instantiate account object with constructor arguments
    BankAccount account("PK0309800780100", "Muhammad Awais", 10000.00);

    // Output account record
    account.displayAccountSummary();

    return 0;
}
