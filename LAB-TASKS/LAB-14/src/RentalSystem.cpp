#include "RentalSystem.h"

#include <iomanip>
#include <iostream>
#include <sstream>

// Small helper used only in this file: formats a number as money, e.g. 108 -> "$108.00".
static std::string money(double amount) {
    std::ostringstream out;
    out << "$" << std::fixed << std::setprecision(2) << amount;
    return out.str();
}

RentalSystem::RentalSystem() : nextRentalId(1) {
}

// ---------------------------------------------------------------------------
// Lookup helpers
// ---------------------------------------------------------------------------

Vehicle* RentalSystem::findVehicle(int vehicleId) {
    for (std::vector<std::unique_ptr<Vehicle> >::iterator it = fleet.begin(); it != fleet.end(); ++it) {
        if ((*it)->getId() == vehicleId) {
            return it->get();
        }
    }
    return nullptr;
}

const Vehicle* RentalSystem::findVehicle(int vehicleId) const {
    for (std::vector<std::unique_ptr<Vehicle> >::const_iterator it = fleet.begin(); it != fleet.end(); ++it) {
        if ((*it)->getId() == vehicleId) {
            return it->get();
        }
    }
    return nullptr;
}

Customer* RentalSystem::findCustomer(int customerId) {
    for (std::size_t i = 0; i < customers.size(); ++i) {
        if (customers[i].getId() == customerId) {
            return &customers[i];
        }
    }
    return nullptr;
}

const Customer* RentalSystem::findCustomer(int customerId) const {
    for (std::size_t i = 0; i < customers.size(); ++i) {
        if (customers[i].getId() == customerId) {
            return &customers[i];
        }
    }
    return nullptr;
}

// A vehicle can be out on at most one rental at a time, so this finds that one record.
Rental* RentalSystem::findActiveRentalForVehicle(int vehicleId) {
    for (std::size_t i = 0; i < rentals.size(); ++i) {
        if (rentals[i].getVehicleId() == vehicleId && rentals[i].isActive()) {
            return &rentals[i];
        }
    }
    return nullptr;
}

// ---------------------------------------------------------------------------
// Building the company
// ---------------------------------------------------------------------------

bool RentalSystem::addVehicle(std::unique_ptr<Vehicle> vehicle) {
    if (vehicle == nullptr) {
        std::cout << "  REJECTED: cannot add an empty vehicle.\n";
        return false;
    }
    if (findVehicle(vehicle->getId()) != nullptr) {
        std::cout << "  REJECTED: a vehicle with id " << vehicle->getId()
                  << " is already in the fleet.\n";
        return false;
    }

    // Calls through the base pointer pick the right override for Car / Motorbike / Truck.
    std::cout << "  Added " << vehicle->typeName() << ": " << vehicle->getMakeModel()
              << " (id " << vehicle->getId() << ", " << vehicle->specification()
              << ", " << money(vehicle->getDailyRate()) << " per day)\n";

    fleet.push_back(std::move(vehicle));   // the fleet now owns it
    return true;
}

bool RentalSystem::registerCustomer(int customerId, const std::string& name) {
    if (findCustomer(customerId) != nullptr) {
        std::cout << "  REJECTED: customer id " << customerId << " is already registered.\n";
        return false;
    }

    customers.push_back(Customer(customerId, name));
    std::cout << "  Registered customer: " << name << " (id " << customerId << ")\n";
    return true;
}

// ---------------------------------------------------------------------------
// Renting and returning
// ---------------------------------------------------------------------------

bool RentalSystem::rentVehicle(int customerId, int vehicleId, int days) {
    if (days <= 0) {
        std::cout << "  REJECTED: rental duration must be at least 1 day (asked for "
                  << days << ").\n";
        return false;
    }

    Customer* customer = findCustomer(customerId);
    if (customer == nullptr) {
        std::cout << "  REJECTED: no customer registered with id " << customerId << ".\n";
        return false;
    }

    Vehicle* vehicle = findVehicle(vehicleId);
    if (vehicle == nullptr) {
        std::cout << "  REJECTED: no vehicle in the fleet with id " << vehicleId << ".\n";
        return false;
    }

    if (customer->hasActiveRental()) {
        std::cout << "  REJECTED: " << customer->getName()
                  << " already has an active rental (one at a time).\n";
        return false;
    }

    if (!vehicle->isAvailable()) {
        std::cout << "  REJECTED: " << vehicle->getMakeModel()
                  << " is already rented out.\n";
        return false;
    }

    // *** Runtime polymorphism ***
    // "vehicle" is a Vehicle*, but the object behind it is a Car, a Motorbike or a Truck.
    // The matching calculateCost() override runs, so the truck surcharge and the motorbike
    // long-rental discount are applied without this function knowing anything about them.
    double cost = vehicle->calculateCost(days);

    rentals.push_back(Rental(nextRentalId, customerId, vehicleId, days, cost));
    nextRentalId++;

    // Both status flags are updated here, together, so they can never disagree.
    vehicle->markAsRented();
    customer->startRental();

    std::cout << "  OK: rental #" << rentals.back().getRentalId() << " - "
              << customer->getName() << " rents " << vehicle->getMakeModel()
              << " (" << vehicle->typeName() << ") for " << days << " day(s). Cost: "
              << money(cost) << "\n";
    return true;
}

bool RentalSystem::returnVehicle(int vehicleId) {
    Vehicle* vehicle = findVehicle(vehicleId);
    if (vehicle == nullptr) {
        std::cout << "  REJECTED: no vehicle in the fleet with id " << vehicleId << ".\n";
        return false;
    }

    Rental* rental = findActiveRentalForVehicle(vehicleId);
    if (rental == nullptr) {
        std::cout << "  REJECTED: " << vehicle->getMakeModel()
                  << " is not currently rented, so there is nothing to return.\n";
        return false;
    }

    // The record is closed, not deleted: the rental history stays complete.
    rental->close();
    vehicle->markAsReturned();

    Customer* customer = findCustomer(rental->getCustomerId());
    if (customer != nullptr) {
        customer->endRental();
    }

    std::cout << "  OK: " << vehicle->getMakeModel() << " returned. Rental #"
              << rental->getRentalId() << " is now closed";
    if (customer != nullptr) {
        std::cout << " and " << customer->getName() << " can rent again";
    }
    std::cout << ".\n";
    return true;
}

// ---------------------------------------------------------------------------
// Reporting
// ---------------------------------------------------------------------------

void RentalSystem::printActiveRentals() const {
    std::cout << "\n--- ACTIVE RENTALS ---\n";

    int activeCount = 0;
    for (std::size_t i = 0; i < rentals.size(); ++i) {
        if (rentals[i].isActive()) {
            activeCount++;
        }
    }

    if (activeCount == 0) {
        std::cout << "  (none)\n";
        return;
    }

    std::cout << "  " << std::left
              << std::setw(6)  << "No."
              << std::setw(20) << "Customer"
              << std::setw(22) << "Vehicle"
              << std::setw(12) << "Type"
              << std::setw(7)  << "Days"
              << "Cost\n";
    std::cout << "  " << std::string(76, '-') << "\n";

    for (std::size_t i = 0; i < rentals.size(); ++i) {
        const Rental& rental = rentals[i];
        if (!rental.isActive()) {
            continue;
        }

        const Customer* customer = findCustomer(rental.getCustomerId());
        const Vehicle* vehicle = findVehicle(rental.getVehicleId());

        std::cout << "  " << std::left
                  << std::setw(6)  << ("#" + std::to_string(rental.getRentalId()))
                  << std::setw(20) << (customer != nullptr ? customer->getName() : "<unknown>")
                  << std::setw(22) << (vehicle != nullptr ? vehicle->getMakeModel() : "<unknown>")
                  // typeName() is virtual: each vehicle labels itself.
                  << std::setw(12) << (vehicle != nullptr ? vehicle->typeName() : "-")
                  << std::setw(7)  << rental.getDays()
                  << money(rental.getTotalCost()) << "\n";
    }
}

void RentalSystem::printRentalHistory() const {
    std::cout << "\n--- RENTAL HISTORY (closed rentals are kept) ---\n";

    if (rentals.empty()) {
        std::cout << "  (none)\n";
        return;
    }

    std::cout << "  " << std::left
              << std::setw(6)  << "No."
              << std::setw(20) << "Customer"
              << std::setw(22) << "Vehicle"
              << std::setw(7)  << "Days"
              << std::setw(12) << "Cost"
              << "Status\n";
    std::cout << "  " << std::string(76, '-') << "\n";

    for (std::size_t i = 0; i < rentals.size(); ++i) {
        const Rental& rental = rentals[i];
        const Customer* customer = findCustomer(rental.getCustomerId());
        const Vehicle* vehicle = findVehicle(rental.getVehicleId());

        std::cout << "  " << std::left
                  << std::setw(6)  << ("#" + std::to_string(rental.getRentalId()))
                  << std::setw(20) << (customer != nullptr ? customer->getName() : "<unknown>")
                  << std::setw(22) << (vehicle != nullptr ? vehicle->getMakeModel() : "<unknown>")
                  << std::setw(7)  << rental.getDays()
                  << std::setw(12) << money(rental.getTotalCost())
                  << (rental.isActive() ? "ACTIVE" : "CLOSED") << "\n";
    }
}

void RentalSystem::printFleetAvailability() const {
    std::cout << "\n--- FLEET AVAILABILITY ---\n";

    int available = 0;
    int rented = 0;
    for (std::size_t i = 0; i < fleet.size(); ++i) {
        if (fleet[i]->isAvailable()) {
            available++;
        } else {
            rented++;
        }
    }

    std::cout << "  Available vehicles: " << available << "\n";
    std::cout << "  Rented vehicles   : " << rented << "\n";
    std::cout << "  Total in fleet    : " << fleet.size() << "\n";

    if (fleet.empty()) {
        return;
    }

    std::cout << "\n  " << std::left
              << std::setw(6)  << "Id"
              << std::setw(22) << "Vehicle"
              << std::setw(12) << "Type"
              << std::setw(20) << "Specification"
              << std::setw(11) << "Rate/day"
              << "Status\n";
    std::cout << "  " << std::string(76, '-') << "\n";

    for (std::size_t i = 0; i < fleet.size(); ++i) {
        // Every call below goes through the base class pointer stored in the vector,
        // and each vehicle answers for itself.
        const Vehicle& vehicle = *fleet[i];
        std::cout << "  " << std::left
                  << std::setw(6)  << vehicle.getId()
                  << std::setw(22) << vehicle.getMakeModel()
                  << std::setw(12) << vehicle.typeName()
                  << std::setw(20) << vehicle.specification()
                  << std::setw(11) << money(vehicle.getDailyRate())
                  << (vehicle.isAvailable() ? "Available" : "Rented out") << "\n";
    }
}

void RentalSystem::printSummary() const {
    std::cout << "\n============================ SUMMARY ============================\n";
    printActiveRentals();
    printRentalHistory();
    printFleetAvailability();
    std::cout << "=================================================================\n";
}
