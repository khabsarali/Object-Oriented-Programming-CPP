#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

// Abstract base class for everything in the fleet.
//
// A plain "Vehicle" is not a real thing we can rent out: the rental price depends on the
// vehicle type (normal / surcharged / discounted), so a generic vehicle could not answer
// calculateCost() sensibly. That is why the pricing and description functions are pure
// virtual and this class cannot be instantiated.
class Vehicle {
private:
    int id;                  // unique id used to find this vehicle in the fleet
    std::string makeModel;   // e.g. "Toyota Corolla"
    double dailyRate;        // rental rate per day
    bool available;          // false while the vehicle is out on rent

protected:
    // Protected: only derived classes (Car, Motorbike, Truck) can build a Vehicle.
    Vehicle(int id, const std::string& makeModel, double dailyRate);

public:
    // Virtual destructor: vehicles are deleted through a Vehicle* (unique_ptr<Vehicle>),
    // so the derived part must be destroyed correctly.
    virtual ~Vehicle();

    // ---- common data, shared by every vehicle type ----
    int getId() const;
    const std::string& getMakeModel() const;
    double getDailyRate() const;
    bool isAvailable() const;

    // Availability is changed only by RentalSystem, when a rental starts or ends.
    void markAsRented();
    void markAsReturned();

    // ---- the contract every vehicle type must fulfil ----

    // Total cost of renting this vehicle for the given number of days.
    // Each subclass applies its own rule (surcharge / discount / plain rate).
    virtual double calculateCost(int days) const = 0;

    // "Car" / "Motorbike" / "Truck" - used when printing summaries.
    virtual std::string typeName() const = 0;

    // The type-specific attribute as text, e.g. "5 seats" or "8 tonne payload".
    // The base class cannot produce this because it does not hold that data.
    virtual std::string specification() const = 0;
};

#endif
