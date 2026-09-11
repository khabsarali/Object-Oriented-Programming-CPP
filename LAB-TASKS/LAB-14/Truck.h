#ifndef TRUCK_H
#define TRUCK_H

#include <string>
#include "Vehicle.h"

// A Truck is a Vehicle. Its extra attribute is the payload capacity in tonnes,
// and every truck rental carries a 20% surcharge.
class Truck : public Vehicle {
private:
    double payloadTonnes;

public:
    Truck(int id, const std::string& makeModel, double dailyRate, double payloadTonnes);

    double getPayloadTonnes() const;

    double calculateCost(int days) const override;
    std::string typeName() const override;
    std::string specification() const override;
};

#endif
