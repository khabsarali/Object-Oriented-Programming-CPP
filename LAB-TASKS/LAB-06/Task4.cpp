#include <iostream>
#include <string>

using namespace std;

// Base class with virtual destructor for proper polymorphic cleanup
class Device {
private:
    string* deviceName;
    string* deviceIdentifier;

public:
    Device(string name, string id) {
        deviceName = new string(name);
        deviceIdentifier = new string(id);
        cout << "[Device] Base constructor: Heap memory allocated for device identifiers." << endl;
    }

    // Virtual destructor guarantees derived destructor is called when deleted via base pointer
    virtual ~Device() {
        delete deviceName;
        delete deviceIdentifier;
        cout << "[Device] Base destructor: Device heap memory successfully released." << endl;
    }

    string getName() const { return *deviceName; }
    string getId() const { return *deviceIdentifier; }
};

// Derived class with additional dynamic heap allocations
class Sensor : public Device {
private:
    string* sensorType;
    float* readingValue;

public:
    Sensor(string name, string id, string type, float val)
        : Device(name, id) {
        sensorType = new string(type);
        readingValue = new float(val);
        cout << "[Sensor] Derived constructor: Heap memory allocated for sensor metrics." << endl;
    }

    ~Sensor() {
        delete sensorType;
        delete readingValue;
        cout << "[Sensor] Derived destructor: Sensor metric memory successfully released." << endl;
    }

    void displayTelemetry() const {
        cout << "\n--- Sensor Telemetry Report ---" << endl;
        cout << "Device Name   : " << getName() << endl;
        cout << "Device ID     : " << getId() << endl;
        cout << "Sensor Type   : " << *sensorType << endl;
        cout << "Reading Value : " << *readingValue << endl;
        cout << "--------------------------------\n" << endl;
    }
};

int main() {
    // Dynamically allocate Sensor object
    Sensor* tempSensor = new Sensor("Thermometer", "TH-101", "Temperature (Celsius)", 36.9f);

    // Output sensor metrics
    tempSensor->displayTelemetry();

    // Clean up memory (triggers derived destructor then base destructor)
    delete tempSensor;
    tempSensor = nullptr;

    return 0;
}
