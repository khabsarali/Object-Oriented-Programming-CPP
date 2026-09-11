#ifndef HEADER1_H
#define HEADER1_H

#include <iostream>
#include <string>

using namespace std;

// Class demonstrating encapsulation with validation logic in mutators
class Product {
private:
    string itemName;
    double unitPrice;
    int stockQuantity;

public:
    // Setters with validation checks
    void setName(const string& name) {
        if (!name.empty()) {
            itemName = name;
        } else {
            cout << "[Validation Warning] Product name cannot be empty." << endl;
        }
    }

    void setPrice(double price) {
        if (price > 0.0) {
            unitPrice = price;
        } else {
            cout << "[Validation Warning] Price must be greater than zero." << endl;
        }
    }

    void setQuantity(int qty) {
        if (qty >= 0) {
            stockQuantity = qty;
        } else {
            cout << "[Validation Warning] Quantity cannot be negative." << endl;
        }
    }

    // Getter functions
    string getName() const {
        return itemName;
    }

    double getPrice() const {
        return unitPrice;
    }

    int getQuantity() const {
        return stockQuantity;
    }
};

#endif
