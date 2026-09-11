#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <iostream>

using namespace std;

// Class definition for Rectangle geometry
class Rectangle {
public:
    double length;
    double width;

    // Member function declarations
    void readDimensions();
    double computeArea();
    double computePerimeter();
};

// Member function definitions outside the class using scope resolution operator ::
void Rectangle::readDimensions() {
    cout << "Enter rectangle length: ";
    cin >> length;
    cout << "Enter rectangle width: ";
    cin >> width;
}

double Rectangle::computeArea() {
    return length * width;
}

double Rectangle::computePerimeter() {
    return 2.0 * (length + width);
}

#endif
