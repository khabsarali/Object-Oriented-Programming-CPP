#include <iostream>
#include <string>

using namespace std;

// Base class representing a general retail product
class Product {
private:
    string productName;
    int productPrice;

public:
    // Default constructor
    Product() : productName("Not Assigned"), productPrice(0) {}

    // Parameterized constructor
    Product(string name, int price) : productName(name), productPrice(price) {}

    void printProductDetails() const {
        cout << "--- Product Specifications ---" << endl;
        cout << "Name  : " << productName << endl;
        cout << "Price : $" << productPrice << endl;
    }
};

// Derived class representing electronic goods
class Electronics : public Product {
private:
    int warrantyPeriodYears;

public:
    // Constructor chaining: delegating base attributes to Product constructor
    Electronics(string name, int price, int warrantyYears)
        : Product(name, price), warrantyPeriodYears(warrantyYears) {}

    void printFullDetails() const {
        printProductDetails();
        cout << "Warranty : " << warrantyPeriodYears << " year(s)" << endl;
    }
};

int main() {
    Electronics tvItem("Smart LED TV", 78000, 4);
    tvItem.printFullDetails();

    return 0;
}
