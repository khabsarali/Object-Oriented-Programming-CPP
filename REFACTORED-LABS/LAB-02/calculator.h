#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>

using namespace std;

// Class providing fundamental arithmetic operations
class Calculator {
public:
    double operand1;
    double operand2;

    // Declarations for arithmetic methods
    double add(double a, double b);
    double subtract(double a, double b);
    double multiply(double a, double b);
    double divide(double a, double b);
};

// Definitions implemented outside the class
double Calculator::add(double a, double b) {
    return a + b;
}

double Calculator::subtract(double a, double b) {
    return a - b;
}

double Calculator::multiply(double a, double b) {
    return a * b;
}

double Calculator::divide(double a, double b) {
    if (b == 0) {
        cout << "Error: Division by zero is undefined!" << endl;
        return 0;
    }
    return a / b;
}

#endif
