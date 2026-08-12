#ifndef MOTORBIKE_H
#define MOTORBIKE_H

#include <string>
#include "Vehicle.h"

// A Motorbike is a Vehicle. Its extra attribute is the engine capacity in cc,
// and long rentals (more than 7 days) get a 10% discount.
class Motorbike : public Vehicle {
private:
    int engineCC;

public:
    Motorbike(int id, const std::string& makeModel, double dailyRate, int engineCC);

    int getEngineCC() const;

    double calculateCost(int days) const override;
    std::string typeName() const override;
    std::string specification() const override;
};

#endif
