#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <iostream>

using namespace std;

// Class to handle temperature conversions
class Temperature {
public:
    double celsiusValue;
    double fahrenheitValue;

    // Convert stored Celsius temperature to Fahrenheit
    void convertToFahrenheit() {
        cout << "Enter temperature in Celsius: ";
        cin >> celsiusValue;
        fahrenheitValue = (celsiusValue * (9.0 / 5.0)) + 32.0;
    }

    // Display the converted temperature
    void displayResult() {
        cout << celsiusValue << " Celsius = " << fahrenheitValue << " Fahrenheit" << endl;
    }
};

#endif
