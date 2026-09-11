#include <iostream>

using namespace std;

// Abstract base class representing a geometric shape
class Shape {
public:
    // Virtual function to enable dynamic (runtime) dispatch
    virtual double calculateArea() const {
        return 0.0;
    }

    // Virtual destructor ensuring proper cleanup in polymorphic usage
    virtual ~Shape() {}
};

// Derived class for Rectangle
class Rectangle : public Shape {
private:
    double length;
    double width;

public:
    Rectangle(double l, double w) : length(l), width(w) {}

    // Override the base virtual function
    double calculateArea() const override {
        return length * width;
    }
};

// Derived class for Circle
class Circle : public Shape {
private:
    double radius;
    const double PI = 3.141592653589793;

public:
    Circle(double r) : radius(r) {}

    // Override the base virtual function
    double calculateArea() const override {
        return PI * radius * radius;
    }
};

int main() {
    // Dynamic polymorphism: Base pointers pointing to derived objects
    Shape* rectShape = new Rectangle(5.0, 3.0);
    Shape* circleShape = new Circle(2.0);

    // Dynamic dispatch invokes the overridden methods at runtime
    cout << "Calculated area of rectangle: " << rectShape->calculateArea() << endl;
    cout << "Calculated area of circle   : " << circleShape->calculateArea() << endl;

    // Free allocated memory
    delete rectShape;
    delete circleShape;

    return 0;
}
