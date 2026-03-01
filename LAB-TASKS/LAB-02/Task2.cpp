#include <iostream>
using namespace std;

class Rectangle {
public:
    int length;
    int width;


    void setDimensions();   // Function declaration
    int area();             // Function declaration
    int perimeter();        // Function declaration
};

// Defining member functions outside the class

void Rectangle::setDimensions() {
    cout << "Enter length: ";
    cin >> length;
    cout << "Enter width: ";
    cin >> width;
}

int Rectangle::area() {
    return length * width;
}

int Rectangle::perimeter() {
    return 2 * (length + width);
}

int main() {
    Rectangle rect;

    rect.setDimensions();

    cout << "Area of rectangle: " << rect.area() << endl;
    cout << "Perimeter of rectangle: " << rect.perimeter() << endl;

    return 0;
}

