// Lab 11 & 12 - Task 3
// Concept: Static data member shared by every object of the class.
// Bank Account System - counting how many accounts were created.

#include <iostream>
#include <string>

using namespace std;

class BankAccount {
private:
    string holderName;
    double balance;

public:
    // Static data member: ONE copy exists for the whole class,
    // not one copy per object.
    static int totalAccounts;

    BankAccount(string name, double bal) : holderName(name), balance(bal) {
        // Every time an object is constructed the shared counter grows
        totalAccounts++;
    }

    void display() const {
        cout << "Account Holder: " << holderName << " | Balance: " << balance << endl;
    }
};

// Static members must be defined once outside the class
int BankAccount::totalAccounts = 0;

int main() {
    cout << "Accounts before creating objects: " << BankAccount::totalAccounts << endl << endl;

    BankAccount a1("Ali", 50000);
    BankAccount a2("Ahmed", 75000);
    BankAccount a3("Hassan", 40000);

    a1.display();
    a2.display();
    a3.display();

    cout << "\nTotal number of bank accounts: " << BankAccount::totalAccounts << endl;

    // Proof that the variable is SHARED: every object reports the same value
    cout << "\nSame counter seen through each object:" << endl;
    cout << "a1 sees: " << a1.totalAccounts << endl;
    cout << "a2 sees: " << a2.totalAccounts << endl;
    cout << "a3 sees: " << a3.totalAccounts << endl;

    return 0;
}
