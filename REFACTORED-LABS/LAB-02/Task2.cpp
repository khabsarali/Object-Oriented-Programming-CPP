#include <iostream>
#include "rectangle.h"

using namespace std;

int main() {
    Rectangle rect;

    // Prompt user for dimensions
    rect.readDimensions();

    // Display calculated results
    cout << "\nCalculated Area      : " << rect.computeArea() << endl;
    cout << "Calculated Perimeter : " << rect.computePerimeter() << endl;

    return 0;
}
