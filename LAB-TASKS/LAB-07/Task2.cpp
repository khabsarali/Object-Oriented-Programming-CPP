#include <iostream>
#include <string>

using namespace std;

// Independent utility class for arithmetic operations
class CalculatorTool {
public:
    double add(double num1, double num2) {
        return num1 + num2;
    }

    double multiply(double num1, double num2) {
        return num1 * num2;
    }
};

// Class demonstrating Aggregation: Student holds a loose reference (pointer) to an external CalculatorTool
class Student {
private:
    string studentName;
    CalculatorTool* sharedCalculator; // Aggregated reference; life not tied to Student

public:
    Student(string name, CalculatorTool* toolPtr)
        : studentName(name), sharedCalculator(toolPtr) {}

    void calculateSum(double a, double b) {
        if (sharedCalculator != nullptr) {
            double res = sharedCalculator->add(a, b);
            cout << studentName << " computed addition (" << a << " + " << b << ") = " << res << endl;
        }
    }

    void calculateProduct(double a, double b) {
        if (sharedCalculator != nullptr) {
            double res = sharedCalculator->multiply(a, b);
            cout << studentName << " computed product (" << a << " * " << b << ") = " << res << endl;
        }
    }
};

int main() {
    // Single shared resource existing independently
    CalculatorTool sharedDeskCalculator;

    // Multiple students sharing the same calculator via aggregation
    Student student1("Student 01", &sharedDeskCalculator);
    Student student2("Student 02", &sharedDeskCalculator);

    cout << "=== Aggregation Demonstration ===" << endl;
    student1.calculateSum(5.5, 6.5);
    student1.calculateProduct(5.0, 6.0);

    cout << endl;
    student2.calculateSum(4.5, 3.5);
    student2.calculateProduct(3.0, 2.0);

    return 0;
}
