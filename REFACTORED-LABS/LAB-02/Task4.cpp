#include <iostream>
#include "temperature.h"

using namespace std;

int main() {
    Temperature tempObj;

    // Run temperature conversion
    tempObj.convertToFahrenheit();

    // Show result
    tempObj.displayResult();

    return 0;
}
