#include <iostream>

using namespace std;

// Class representing a dedicated display unit (Component in Composition)
class DisplayUnit {
private:
    double lastComputedValue;

public:
    DisplayUnit() : lastComputedValue(0.0) {}

    // Output and store the current computed result
    void renderResult(double val) {
        lastComputedValue = val;
        cout << "Display Screen -> Current Output: " << lastComputedValue << endl;
    }

    // Retrieve cached previous result
    double getStoredValue() const {
        return lastComputedValue;
    }
};

// Class demonstrating Composition: Calculator "has-a" DisplayUnit embedded by value
class Calculator {
private:
    DisplayUnit display; // Tightly coupled component; lifetime bound to Calculator

public:
    Calculator() {}

    void performAddition(double x, double y) {
        double result = x + y;
        display.renderResult(result);
    }

    void performMultiplication(double x, double y) {
        double result = x * y;
        display.renderResult(result);
    }

    void showMemoryRecall() const {
        cout << "Display Memory Recall: " << display.getStoredValue() << endl;
    }
};

int main() {
    Calculator calcDevice;

    cout << "--- Performing Math Operations (Composition Demo) ---" << endl;
    calcDevice.performAddition(6.4, 5.6);
    calcDevice.performMultiplication(1.5, 3.0);
    calcDevice.showMemoryRecall();

    return 0;
}
