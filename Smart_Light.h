#pragma once

#include "Device.h"
#include <iostream>

///////////////////////////////////////////////
//Smart_Light.h class, responsible for functionality of a smart light device
////////////////////////////////////////////////
using namespace std;

class Smart_Light : public Device {
private:
    int brightness;
    string colorType;
public:
    Smart_Light(int id, const string& name, int brightness, const string& colorType)
        : Device(id, name, "Light"), brightness(brightness), colorType(colorType) {
    }

    void InteractionEvent() override {
        if (!status) {
            cout << "Type: " << getType() << " | " << getName() << " is not active. Turn on the device \n";
        }
        else {
            cout << "Type: " << getType() << " | " << "Name: " << getName() << ": Brightness - " << brightness << ", Color - " << colorType << ".\n";
        }
    }

    int getBrightness() const { return brightness; }
    void setBrightness(int new_brightness) { brightness = new_brightness; }

    string getColorType() const { return colorType; }
    void setColorType(const std::string& new_color) { colorType = new_color; }
};
