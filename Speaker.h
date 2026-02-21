#pragma once

#include "Device.h"
#include <iostream>
#include <string>

/// <summary>
/// Speaker.h, class responsible for functionality of Speaker device
/// </summary>
using namespace std;
class Speaker : public Device {
private:
    int volumeLevel;
public:
    Speaker(int id, const string& name, int volumeLevel)
        : Device(id, name, "Speaker"), volumeLevel(volumeLevel) {
    }

    void InteractionEvent() override {
        if (!status) {
            cout << "Type: " << getType() << " | " << getName() << " is not active. Turn on the device \n";
        }
        else {
            cout << "Type: " << getType() << " | " << "Name: " << getName() << ": Volume level - " << volumeLevel << ".\n";
        }
    }

    int getVolumeLevel() const { return volumeLevel; }
    void setVolumeLevel(int new_volume) { volumeLevel = new_volume; }
};

