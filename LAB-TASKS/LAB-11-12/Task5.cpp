// Lab 11 & 12 - Task 5
// Concept: Abstract class, pure virtual function and runtime polymorphism.
// Hospital Staff System.

#include <iostream>
#include <string>

using namespace std;

// Abstract base class: it has at least one pure virtual function,
// so objects of HospitalStaff can NOT be created.
class HospitalStaff {
protected:
    string name;

public:
    HospitalStaff(string n) : name(n) {}

    // Pure virtual function ( = 0 ) - every derived class must define it
    virtual void performDuty() = 0;

    // Virtual destructor so deleting through a base pointer is safe
    virtual ~HospitalStaff() {}
};

class Doctor : public HospitalStaff {
public:
    Doctor(string n) : HospitalStaff(n) {}

    void performDuty() {
        cout << name << " (Doctor) is diagnosing patients." << endl;
    }
};

class Nurse : public HospitalStaff {
public:
    Nurse(string n) : HospitalStaff(n) {}

    void performDuty() {
        cout << name << " (Nurse) is assisting patients." << endl;
    }
};

class Receptionist : public HospitalStaff {
public:
    Receptionist(string n) : HospitalStaff(n) {}

    void performDuty() {
        cout << name << " (Receptionist) is managing appointments." << endl;
    }
};

int main() {
    // HospitalStaff s("test");  // <-- ERROR: cannot create an abstract object

    // Base class pointers holding derived class objects
    HospitalStaff* staff[3];
    staff[0] = new Doctor("Dr. Ali");
    staff[1] = new Nurse("Sara");
    staff[2] = new Receptionist("Hassan");

    cout << "--- Hospital Staff Duties ---" << endl;

    // Runtime polymorphism: the correct performDuty() is chosen at run time
    for (int i = 0; i < 3; i++) {
        staff[i]->performDuty();
    }

    // Free the dynamically allocated memory
    for (int i = 0; i < 3; i++) {
        delete staff[i];
    }

    return 0;
}
