#include "Rental.h"

Rental::Rental(int rentalId, int customerId, int vehicleId, int days, double totalCost)
    : rentalId(rentalId), customerId(customerId), vehicleId(vehicleId),
      days(days), totalCost(totalCost), active(true) {
    // A rental starts active and stays in the system for good.
}

int Rental::getRentalId() const {
    return rentalId;
}

int Rental::getCustomerId() const {
    return customerId;
}

int Rental::getVehicleId() const {
    return vehicleId;
}

int Rental::getDays() const {
    return days;
}

double Rental::getTotalCost() const {
    return totalCost;
}

bool Rental::isActive() const {
    return active;
}

// The vehicle came back: close the record, but keep it as history.
void Rental::close() {
    active = false;
}
