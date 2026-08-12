#include "Truck.h"

#include <iomanip>
#include <sstream>

Truck::Truck(int id, const std::string& makeModel, double dailyRate, double payloadTonnes)
    : Vehicle(id, makeModel, dailyRate), payloadTonnes(payloadTonnes) {
}

double Truck::getPayloadTonnes() const {
    return payloadTonnes;
}

// Every truck rental carries a 20% surcharge on top of the normal cost.
double Truck::calculateCost(int days) const {
    const double surchargeMultiplier = 1.20;   // 20% extra

    double baseCost = getDailyRate() * days;
    return baseCost * surchargeMultiplier;
}

std::string Truck::typeName() const {
    return "Truck";
}

std::string Truck::specification() const {
    // std::to_string on a double would print "8.000000", so the text is built here instead.
    std::ostringstream out;
    out << std::fixed << std::setprecision(1) << payloadTonnes << " tonne payload";
    return out.str();
}
