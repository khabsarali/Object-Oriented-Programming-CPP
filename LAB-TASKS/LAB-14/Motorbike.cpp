#include "Motorbike.h"

Motorbike::Motorbike(int id, const std::string& makeModel, double dailyRate, int engineCC)
    : Vehicle(id, makeModel, dailyRate), engineCC(engineCC) {
}

int Motorbike::getEngineCC() const {
    return engineCC;
}

// A motorbike gets a 10% discount when the rental is longer than 7 days.
// A rental of 7 days or fewer is charged at the normal rate.
double Motorbike::calculateCost(int days) const {
    const int discountAfterDays = 7;
    const double discountMultiplier = 0.90;   // 10% off

    double baseCost = getDailyRate() * days;
    if (days > discountAfterDays) {
        return baseCost * discountMultiplier;
    }
    return baseCost;
}

std::string Motorbike::typeName() const {
    return "Motorbike";
}

std::string Motorbike::specification() const {
    return std::to_string(engineCC) + " cc engine";
}
