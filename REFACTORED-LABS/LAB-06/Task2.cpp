#include <iostream>
#include <string>

using namespace std;

// Grandparent class in inheritance chain
class Vehicle {
public:
    Vehicle(string category) {
        cout << "[1] Vehicle constructor executed: Category = " << category << endl;
    }
};

// Parent class inheriting from Vehicle
class Car : public Vehicle {
public:
    Car(string category, string make) : Vehicle(category) {
        cout << "[2] Car constructor executed: Make = " << make << endl;
    }
};

// Child class inheriting from Car
class ElectricCar : public Car {
public:
    ElectricCar(string category, string make, string batteryCapacity)
        : Car(category, make) {
        cout << "[3] ElectricCar constructor executed: Battery = " << batteryCapacity << endl;
    }
};

int main() {
    cout << "--- Instantiating ElectricCar Object ---" << endl;
    // Constructor chain executes from base (Vehicle) -> Car -> ElectricCar
    ElectricCar tesla("Passenger Transport", "Tesla", "150kWh");

    return 0;
}
