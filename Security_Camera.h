
#pragma once

#include "Device.h"
#include <iostream>
#include <string>

using namespace std;

class Security_Camera : public Device {
private:
    string quality;
    string power;
public:
    // constructor
    Security_Camera(int id, const string& name, const string& quality, const string& power)
        : Device(id, name, "Camera"), quality(quality), power(power) {
    }

    void InteractionEvent() override {
        if (!status) {
            cout << "Type: " << getType() << " | " << getName() << " is not active. Turn on the device \n";
        }
        else {
            cout << "Type: " << getType() << " | " << "Name: " << getName() << ": Quality - " << quality << ", Power - " << power << ".\n";
        }
    }

    string getQuality() const { return quality; }
    void setQuality(const string& new_quality) { quality = new_quality; }

    string getPower() const { return power; }
    void setPower(const string& new_power) { power = new_power; }
};
