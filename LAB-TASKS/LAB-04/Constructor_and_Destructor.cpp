#include <iostream>

using namespace std;

// Class demonstrating constructor and destructor lifecycle
class Locker {
public:
    // Constructor invoked upon object creation
    Locker() {
        cout << "[Lifecycle] Locker has been allocated to the customer." << endl;
    }

    // Destructor invoked automatically when object leaves scope
    ~Locker() {
        cout << "[Lifecycle] Locker has been returned by the customer." << endl;
    }
};

int main() {
    cout << "Program starting: Creating a locker instance..." << endl;

    // Creating object within local scope
    Locker locker1;

    cout << "Program ending: Exiting main scope..." << endl;
    return 0;
}
