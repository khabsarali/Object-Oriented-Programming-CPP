#include "Customer.h"

Customer::Customer(int id, const std::string& name)
    : id(id), name(name), activeRental(false) {
    // A new customer starts with no rental.
}

int Customer::getId() const {
    return id;
}

const std::string& Customer::getName() const {
    return name;
}

bool Customer::hasActiveRental() const {
    return activeRental;
}

void Customer::startRental() {
    activeRental = true;
}

void Customer::endRental() {
    activeRental = false;
}
