#include <iostream>
#include "calculator.h"

using namespace std;

int main() {
    Calculator calc;
    double num1, num2;
    char operation;

    cout << "Enter first number: ";
    cin >> num1;

    cout << "Enter second number: ";
    cin >> num2;

    cout << "Select operation (+, -, *, /): ";
    cin >> operation;

    // Execute selected mathematical operation
    switch (operation) {
        case '+':
            cout << "Sum: " << calc.add(num1, num2) << endl;
            break;
        case '-':
            cout << "Difference: " << calc.subtract(num1, num2) << endl;
            break;
        case '*':
        case 'x':
        case 'X':
            cout << "Product: " << calc.multiply(num1, num2) << endl;
            break;
        case '/':
            cout << "Quotient: " << calc.divide(num1, num2) << endl;
            break;
        default:
            cout << "Invalid operator selected." << endl;
            break;
    }

    return 0;
}
