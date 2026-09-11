#include <iostream>

using namespace std;

// Class demonstrating constructor overloading
class Rectangle {
private:
    float length;
    float width;
    float area;

public:
    // 1. Default constructor (dimensions 1.0 x 1.0)
    Rectangle() {
        length = 1.0f;
        width = 1.0f;
        area = 0.0f;
    }

    // 2. Overloaded constructor for rectangle (custom length and width)
    Rectangle(float l, float w) {
        length = l;
        width = w;
        area = 0.0f;
    }

    // 3. Overloaded constructor for square (equal sides)
    Rectangle(float side) {
        length = side;
        width = side;
        area = 0.0f;
    }

    // Calculate the area from current dimensions
    void computeArea() {
        area = length * width;
    }

    // Display the calculated area
    void showArea() const {
        cout << "Dimensions: " << length << " x " << width << " | Calculated Area = " << area << endl;
    }
};

int main() {
    // Case 1: Custom rectangle with two parameters
    Rectangle rect1(2.0f, 3.0f);
    rect1.computeArea();
    rect1.showArea();

    // Case 2: Square with single parameter
    Rectangle rect2(4.0f);
    rect2.computeArea();
    rect2.showArea();

    // Case 3: Default rectangle (1.0 x 1.0)
    Rectangle rect3;
    rect3.computeArea();
    rect3.showArea();

    return 0;
}
