#include <iostream>

using namespace std;

// Class template for basic arithmetic operations
template <typename T>
class ArithmeticCalculator {
private:
    T operand1;
    T operand2;

public:
    // Constructor
    ArithmeticCalculator(T op1, T op2) : operand1(op1), operand2(op2) {}

    T add() const {
        return operand1 + operand2;
    }

    T subtract() const {
        return operand1 - operand2;
    }

    T multiply() const {
        return operand1 * operand2;
    }
};

int main() {
    // Integer operations test
    int intA, intB;
    cout << "Enter two integers: ";
    cin >> intA >> intB;

    ArithmeticCalculator<int> intCalc(intA, intB);
    cout << "\n--- Integer Results ---" << endl;
    cout << "Addition       : " << intCalc.add() << endl;
    cout << "Subtraction    : " << intCalc.subtract() << endl;
    cout << "Multiplication : " << intCalc.multiply() << endl;

    // Floating-point operations test
    double dblA, dblB;
    cout << "\nEnter two double values: ";
    cin >> dblA >> dblB;

    ArithmeticCalculator<double> dblCalc(dblA, dblB);
    cout << "\n--- Double Results ---" << endl;
    cout << "Addition       : " << dblCalc.add() << endl;
    cout << "Subtraction    : " << dblCalc.subtract() << endl;
    cout << "Multiplication : " << dblCalc.multiply() << endl;

    return 0;
}
