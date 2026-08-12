#include "Car.h"

Car::Car(int id, const std::string& makeModel, double dailyRate, int seats)
    : Vehicle(id, makeModel, dailyRate), seats(seats) {
}

int Car::getSeats() const {
    return seats;
}

// A car is rented at the plain daily rate: no surcharge and no discount.
double Car::calculateCost(int days) const {
    return getDailyRate() * days;
}

std::string Car::typeName() const {
    return "Car";
}

std::string Car::specification() const {
    return std::to_string(seats) + " seats";
}
