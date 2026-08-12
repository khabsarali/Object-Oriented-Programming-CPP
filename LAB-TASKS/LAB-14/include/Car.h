#ifndef CAR_H
#define CAR_H

#include <string>
#include "Vehicle.h"

// A Car is a Vehicle. Its extra attribute is the number of seats,
// and it is rented at the plain daily rate (no surcharge, no discount).
class Car : public Vehicle {
private:
    int seats;

public:
    Car(int id, const std::string& makeModel, double dailyRate, int seats);

    int getSeats() const;

    double calculateCost(int days) const override;
    std::string typeName() const override;
    std::string specification() const override;
};

#endif
