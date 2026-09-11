#include <iostream>
#include <iomanip>
#include "header1.h"

using namespace std;

int main() {
    Product item;

    // Test validation guards by providing invalid inputs
    cout << "--- Testing Input Validation ---" << endl;
    item.setName("");
    item.setPrice(-49.99);
    item.setQuantity(-3);

    // Assign valid properties to the product
    cout << "\n--- Assigning Valid Product Details ---" << endl;
    item.setName("Laptop");
    item.setPrice(1200.50);
    item.setQuantity(5);

    // Retrieve and display product attributes using getters
    cout << "\n--- Product Information ---" << endl;
    cout << "Product  : " << item.getName() << endl;
    cout << "Price    : $" << fixed << setprecision(2) << item.getPrice() << endl;
    cout << "Quantity : " << item.getQuantity() << " units" << endl;

    return 0;
}
