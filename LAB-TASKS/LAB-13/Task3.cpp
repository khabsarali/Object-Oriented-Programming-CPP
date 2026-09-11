#include <iostream>
#include <string>

using namespace std;

// Class template holding a generic ordered pair
template <typename T>
class DataPair {
private:
    T firstElement;
    T secondElement;

public:
    // Constructor
    DataPair(T first, T second) : firstElement(first), secondElement(second) {}

    // Getters
    T getFirst() const { return firstElement; }
    T getSecond() const { return secondElement; }

    // Display elements
    void printPair() const {
        cout << "First Element  : " << firstElement << endl;
        cout << "Second Element : " << secondElement << endl;
    }
};

int main() {
    cout << "=== Integer DataPair ===" << endl;
    DataPair<int> intPair(10, 20);
    intPair.printPair();

    cout << "\n=== Double DataPair ===" << endl;
    DataPair<double> doublePair(23.4, 19.9);
    doublePair.printPair();

    cout << "\n=== String DataPair ===" << endl;
    DataPair<string> stringPair("Hello", "World");
    stringPair.printPair();

    return 0;
}
