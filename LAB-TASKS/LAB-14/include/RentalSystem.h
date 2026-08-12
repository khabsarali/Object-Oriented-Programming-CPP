#ifndef RENTALSYSTEM_H
#define RENTALSYSTEM_H

#include <memory>
#include <string>
#include <vector>

#include "Customer.h"
#include "Rental.h"
#include "Vehicle.h"

// The rental company itself. It owns the fleet, the customers and every rental record,
// and it is the only class that changes their state - that is what keeps them consistent.
//
// Vehicles are held as unique_ptr<Vehicle> because the fleet is a mixed container of
// Cars, Motorbikes and Trucks: the base pointer is what lets them live together, and
// unique_ptr means they are freed automatically (no delete anywhere in this project).
// Customers and rentals are plain objects, so they are stored by value.
class RentalSystem {
private:
    std::vector<std::unique_ptr<Vehicle> > fleet;
    std::vector<Customer> customers;
    std::vector<Rental> rentals;
    int nextRentalId;

    // Lookup helpers. Two versions of each: the const one is used by the printing
    // functions, which are not allowed to change the system.
    Vehicle* findVehicle(int vehicleId);
    const Vehicle* findVehicle(int vehicleId) const;
    Customer* findCustomer(int customerId);
    const Customer* findCustomer(int customerId) const;
    Rental* findActiveRentalForVehicle(int vehicleId);

public:
    RentalSystem();

    // ---- building the company ----

    // Takes ownership of the vehicle. Rejects a duplicate vehicle id.
    bool addVehicle(std::unique_ptr<Vehicle> vehicle);

    // Rejects a duplicate customer id, so customer ids stay unique.
    bool registerCustomer(int customerId, const std::string& name);

    // ---- the two use cases ----

    // Rents a vehicle to a customer for a number of days.
    // Fails (and explains why) if: the days are not at least 1, the customer or the
    // vehicle does not exist, the customer already has an active rental, or the
    // vehicle is already rented out.
    bool rentVehicle(int customerId, int vehicleId, int days);

    // Returns a rented vehicle: the vehicle becomes available again, the customer is
    // free to rent again, and the rental record is closed but kept.
    bool returnVehicle(int vehicleId);

    // ---- reporting ----
    void printActiveRentals() const;
    void printRentalHistory() const;
    void printFleetAvailability() const;
    void printSummary() const;      // all three of the above, in order
};

#endif
