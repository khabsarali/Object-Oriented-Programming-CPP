#include <iostream>

using namespace std;

// Base class 1: Printer functionality
class Printer {
public:
    void printDocument() {
        cout << "[Printer] Sending document to print queue and generating hardcopy..." << endl;
    }
};

// Base class 2: Scanner functionality
class Scanner {
public:
    void scanDocument() {
        cout << "[Scanner] Optical scan initiated. Digital image captured." << endl;
    }
};

// Derived class demonstrating Multiple Inheritance (Printer + Scanner)
class Photocopier : public Printer, public Scanner {
public:
    // Execute end-to-end photocopy routine
    void makeCopy() {
        cout << "[Photocopier] Starting photocopy job..." << endl;
        scanDocument();   // Method from Scanner base class
        printDocument();  // Method from Printer base class
        cout << "[Photocopier] Photocopy job finished successfully." << endl;
    }
};

int main() {
    Photocopier copierDevice;

    // Test individual base class interfaces
    cout << "--- Testing Standalone Printer Functionality ---" << endl;
    copierDevice.printDocument();

    cout << "\n--- Testing Standalone Scanner Functionality ---" << endl;
    copierDevice.scanDocument();

    // Test combined functionality
    cout << "\n--- Testing Integrated Photocopy Workflow ---" << endl;
    copierDevice.makeCopy();

    return 0;
}
