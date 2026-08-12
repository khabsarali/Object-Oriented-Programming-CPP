#include <iostream>
using namespace std;

/* ========== FUNCTION TEMPLATE ========== */
template <typename T>
void printTwice(T val)
{
    cout << val << endl;
    cout << val << endl;
}

/* ========== MAIN FUNCTION ========== */
int main()
{
    printTwice(5);            // int
    printTwice(3.14);         // double
    printTwice("Hello");      // string

    return 0;
}