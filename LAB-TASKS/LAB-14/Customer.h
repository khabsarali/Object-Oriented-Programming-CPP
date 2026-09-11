#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

// A registered customer of the rental company.
//
// Business rule (R2): a customer may have at most ONE active rental at a time,
// so the customer keeps a flag saying whether one is currently open.
// Only RentalSystem changes that flag, when a rental starts or ends.
class Customer {
private:
    int id;                 // unique customer id
    std::string name;
    bool activeRental;      // true while this customer has an open rental

public:
    Customer(int id, const std::string& name);

    int getId() const;
    const std::string& getName() const;
    bool hasActiveRental() const;

    void startRental();
    void endRental();
};

#endif
