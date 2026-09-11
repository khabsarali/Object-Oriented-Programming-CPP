#ifndef RENTAL_H
#define RENTAL_H

// One rental record: customer X took vehicle Y for N days at an agreed cost.
//
// The record is kept even after the vehicle comes back (R5): returning only closes
// the rental, it never deletes it, so the rental history stays available.
//
// The customer and the vehicle are referred to by their ids rather than by pointers.
// Ids are stable handles - the customers vector may move its elements when it grows,
// which would leave a stored pointer dangling.
//
// The cost is calculated once (through Vehicle::calculateCost) when the rental is created
// and stored here, so a past rental keeps the price that was agreed at the time.
class Rental {
private:
    int rentalId;
    int customerId;
    int vehicleId;
    int days;
    double totalCost;
    bool active;        // true = vehicle still out, false = returned/closed

public:
    Rental(int rentalId, int customerId, int vehicleId, int days, double totalCost);

    int getRentalId() const;
    int getCustomerId() const;
    int getVehicleId() const;
    int getDays() const;
    double getTotalCost() const;
    bool isActive() const;

    // Closes the record when the vehicle is returned. The record itself stays in the system.
    void close();
};

#endif
