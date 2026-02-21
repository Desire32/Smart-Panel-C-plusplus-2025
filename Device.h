#pragma once

#include <string>
#include <iostream>
#include <random>
#include <cstdlib>

using namespace std;


/// <summary>
/// Device.h, basically the skeleton of whole panel, there are parts for devices, methods to get some information, etc.
/// </summary>

class Device {
protected:
    int id;
    string name;
    string type;
    bool status;      // isActive
    bool connected;    // CheckConnection

public:

    Device(int id, const string& name, const string& type)
        : id(id), name(name), type(type), status(false), connected(false) {
    }

    // these are used mostly for correctly showing description of the devices
    int getId() const { return id; }
    string getName() const { return name; }
    string getType() const { return type; }


    bool isActive() const { return status; } // plugged-in part
    bool CheckConnection() const { return connected; } // network part

    virtual void Activate() {
        status = true;
        cout << name << " is now activated.\n";
    }
    virtual void Deactivate() {
        status = false;
        cout << name << " is now deactivated.\n";
    }
    void toggleConnection() {
        if (!status) {
            cout << name << " is not active. Cannot change connection status.\n";
            return;
        }
        connected = !connected;
        cout << name << " connection status is now: "
            << (connected ? "Connected" : "Disconnected") << "\n";
    }

    // interactionEvnt
    virtual void InteractionEvent() = 0;
};