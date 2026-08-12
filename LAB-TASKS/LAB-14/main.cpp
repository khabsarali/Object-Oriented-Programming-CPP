// Lab 14 - Vehicle Rental System
// Object-Oriented Programming with C++
//
// This program runs one complete scenario through the rental company:
// a fleet is built, customers are registered, vehicles are rented (showing the
// truck surcharge and the motorbike long-rental discount), invalid requests are
// rejected, one vehicle is returned, and a summary is printed.

#include <iostream>
#include <memory>

#include "Car.h"
#include "Motorbike.h"
#include "RentalSystem.h"
#include "Truck.h"

int main() {
    RentalSystem system;

    std::cout << "=================================================================\n";
    std::cout << "            VEHICLE RENTAL SYSTEM - Lab 14 Demo\n";
    std::cout << "=================================================================\n";

    // ---------------------------------------------------------------
    // STEP 1: build the fleet (one Car, one Motorbike, one Truck, plus a spare Car)
    // ---------------------------------------------------------------
    std::cout << "\n[STEP 1] Adding vehicles to the fleet\n";
    // make_unique creates the object and hands ownership straight to the system,
    // so there is no raw new/delete anywhere in this project.
    system.addVehicle(std::make_unique<Car>(101, "Toyota Corolla", 45.0, 5));
    system.addVehicle(std::make_unique<Car>(102, "Suzuki Alto", 30.0, 4));
    system.addVehicle(std::make_unique<Motorbike>(201, "Yamaha YBR", 12.0, 125));
    system.addVehicle(std::make_unique<Truck>(301, "Hino 500", 150.0, 8.0));

    // ---------------------------------------------------------------
    // STEP 2: register customers
    // ---------------------------------------------------------------
    std::cout << "\n[STEP 2] Registering customers\n";
    system.registerCustomer(1, "Absar Ali");
    system.registerCustomer(2, "Bilal Khan");
    system.registerCustomer(3, "Hamza Sheikh");
    system.registerCustomer(4, "Sana Malik");   // stays free, used for the checks in step 4

    // ---------------------------------------------------------------
    // STEP 3: process rentals - one of each vehicle type, so all three
    //         pricing rules can be seen in the output
    // ---------------------------------------------------------------
    std::cout << "\n[STEP 3] Processing rentals\n";

    // Car: 45.00 x 3 = 135.00 (plain daily rate)
    system.rentVehicle(1, 101, 3);

    // Motorbike, 10 days: 12.00 x 10 = 120.00, then 10% off = 108.00 (longer than 7 days)
    system.rentVehicle(2, 201, 10);

    // Truck: 150.00 x 4 = 600.00, plus the 20% surcharge = 720.00
    system.rentVehicle(3, 301, 4);

    // ---------------------------------------------------------------
    // STEP 4: invalid requests - these must all be refused
    // ---------------------------------------------------------------
    std::cout << "\n[STEP 4] Checking that invalid requests are rejected\n";

    std::cout << " a) Renting a vehicle that is already rented out:\n";
    system.rentVehicle(4, 101, 2);          // Sana is free, but the Corolla is with customer 1

    std::cout << " b) A customer who already has an active rental:\n";
    system.rentVehicle(1, 102, 5);          // customer 1 still has the Corolla

    std::cout << " c) An invalid rental duration:\n";
    system.rentVehicle(4, 102, 0);          // 0 days
    system.rentVehicle(4, 102, -4);         // negative days

    std::cout << " d) A customer who is not registered:\n";
    system.rentVehicle(99, 102, 3);

    std::cout << " e) A vehicle that is not in the fleet:\n";
    system.rentVehicle(4, 999, 3);

    std::cout << " f) A duplicate customer id:\n";
    system.registerCustomer(1, "Someone Else");

    // ---------------------------------------------------------------
    // STEP 5: return one vehicle
    // ---------------------------------------------------------------
    std::cout << "\n[STEP 5] Returning a vehicle\n";
    system.returnVehicle(101);              // customer 1 brings the Corolla back

    std::cout << " Returning the same vehicle again (already returned):\n";
    system.returnVehicle(101);

    // The return also freed the customer, so the same customer can rent again.
    // In step 4b this exact request was refused; now it goes through.
    std::cout << " The same customer renting again, now that the rental is closed:\n";
    system.rentVehicle(1, 102, 5);          // Suzuki Alto: 30.00 x 5 = 150.00

    // ---------------------------------------------------------------
    // STEP 6: the summary
    // ---------------------------------------------------------------
    std::cout << "\n[STEP 6] Printing the summary\n";
    system.printSummary();

    std::cout << "\nNotice in the summary that rental #1 is CLOSED but still on record,\n";
    std::cout << "that the Corolla is available again, and that Absar Ali was able to start\n";
    std::cout << "rental #4 only after the first rental was closed.\n";

    return 0;
}
