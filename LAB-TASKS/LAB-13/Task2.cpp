#include <iostream>
using namespace std;

/* ========== FUNCTION TEMPLATE ========== */
template <typename T>
T findMin(T a, T b)
{
    if (a < b)
        return a;
    else
        return b;
}

/* ========== MAIN FUNCTION ========== */
int main()
{
    int i1, i2;
    double d1, d2;
    char c1, c2;

    // ===== INTEGER INPUT =====
    cout << "Enter two integers: ";
    cin >> i1 >> i2;
    cout << "Min (int): " << findMin(i1, i2) << endl;

    // ===== DOUBLE INPUT =====
    cout << "\nEnter two doubles: ";
    cin >> d1 >> d2;
    cout << "Min (double): " << findMin(d1, d2) << endl;

    // ===== CHAR INPUT =====
    cout << "\nEnter two characters: ";
    cin >> c1 >> c2;
    cout << "Min (char): " << findMin(c1, c2) << endl;

    return 0;
}