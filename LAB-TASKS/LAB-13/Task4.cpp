#include <iostream>
using namespace std;

/* ========== CLASS TEMPLATE ========== */
template <typename T>
class Calculator {
private:
    T a, b;

public:
    // Constructor
    Calculator(T x, T y) {
        a = x;
        b = y;
    }

    T add() {
        return a + b;
    }

    T subtract() {
        return a - b;
    }

    T multiply() {
        return a * b;
    }
};

/* ========== MAIN FUNCTION ========== */
int main() {

    // ===== INT INPUT =====
    int x1, y1;
    cout << "Enter two integers: ";
    cin >> x1 >> y1;

    Calculator<int> c1(x1, y1);

    cout << "\nINT RESULTS:" << endl;
    cout << "Add: " << c1.add() << endl;
    cout << "Subtract: " << c1.subtract() << endl;
    cout << "Multiply: " << c1.multiply() << endl;

    // ===== DOUBLE INPUT =====
    double x2, y2;
    cout << "\nEnter two doubles: ";
    cin >> x2 >> y2;

    Calculator<double> c2(x2, y2);

    cout << "\nDOUBLE RESULTS:" << endl;
    cout << "Add: " << c2.add() << endl;
    cout << "Subtract: " << c2.subtract() << endl;
    cout << "Multiply: " << c2.multiply() << endl;

    return 0;
}