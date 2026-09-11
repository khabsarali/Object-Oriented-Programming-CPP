#include "Vehicle.h"

Vehicle::Vehicle(int id, const std::string& makeModel, double dailyRate)
    : id(id), makeModel(makeModel), dailyRate(dailyRate), available(true) {
    // A vehicle joins the fleet available.
}

// Defined here (not in the header) so the vtable is emitted in one place.
Vehicle::~Vehicle() {
}

int Vehicle::getId() const {
    return id;
}

const std::string& Vehicle::getMakeModel() const {
    return makeModel;
}

double Vehicle::getDailyRate() const {
    return dailyRate;
}

bool Vehicle::isAvailable() const {
    return available;
}

void Vehicle::markAsRented() {
    available = false;
}

void Vehicle::markAsReturned() {
    available = true;
}
