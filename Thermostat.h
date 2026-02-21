#pragma once

#include "Device.h"
#include <iostream>
#include <string>

using namespace std;
/////////////////////////////////////////////////
// Thermostat.h, responsible for functionality of Thermostat device
////////////////////////////////////////////////

class Thermostat : public Device {
private:
    double temperature;
public:
    Thermostat(int id, const string& name, double temperature)
        : Device(id, name, "Thermostat"), temperature(temperature) {
    }
    void InteractionEvent() override {
        if (!status) {
            cout << "Type: " << getType() << " | " << getName() << " is not active. Turn on the device \n";
        }
        else {
            cout << "Type: " << getType() << " | " << "Name: " << getName() << ": Current temperature - " << temperature << "°C.\n";
        }
    }
    double getTemperature() const { return temperature; }
    void setTemperature(double new_temperature) { temperature = new_temperature; }
};

