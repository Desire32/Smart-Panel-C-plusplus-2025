#include <iostream>
#include <vector>
#include <algorithm>
#include "backend.h"

/// <summary>
/// backend.cpp, consists of polymorphic function for activate a specific device using a pointer, and other functions to manage
/// connection functionality
/// </summary>

using namespace std;

// error constants
const string INVALID_INPUT = "Invalid choice. Please try again.\n";


// made a template in order to not repeat this section many times
template<typename T>
void toggleDevice(T* device) {
    if (device->isActive()) {
        device->Deactivate();
    }
    else {
        device->Activate();
    }
}

void showWorkingStatus(const vector<Device*>& devices) {
    cout << "\n--- Device Status ---\n";

    cout << "Active devices:\n";
    for (const auto& device : devices) {
        if (device->isActive()) {
            cout << device->getName() << " (" << device->getType() << ")\n";
        }
    }
    cout << "\nInactive devices:\n";
    for (const auto& device : devices) {
        if (!device->isActive()) {
            cout << device->getName() << " (" << device->getType() << ")\n";
        }
    }

    int choice;
    while (true) {
        cout << "\n1. Activate/Deactivate a Device\n";
        cout << "2. Back\n";
        cout << "Please choose an option: ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 2) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << INVALID_INPUT;
        }
        else {
            break;
        }
    }

    if (choice == 1) {
        cout << "\nSelect a device to activate/deactivate:\n";
        for (size_t i = 0; i < devices.size(); ++i) {
            cout << i + 1 << ". " << devices[i]->getName() << " (" << devices[i]->getType() << ")\n";
        }

        int deviceChoice;
        while (true) {
            cout << "Enter the device number: ";
            cin >> deviceChoice;

            if (cin.fail() || deviceChoice < 1 || deviceChoice > devices.size()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << INVALID_INPUT;
            }
            else {
                break;
            }
        }
        toggleDevice(devices[deviceChoice - 1]);
    }
}

///////////////////////////
// bool single true for single use, all true apply for all (depends on user's choice)
/////////////////
void changeDeviceConnection(vector<Room*>& rooms, vector<Device*>& devices, bool single, bool all) {
    if (single) {
        string deviceName;
        cout << "\nEnter the name of the device to change connection status: ";
        getline(cin, deviceName);
        auto it = find_if(devices.begin(), devices.end(), [&deviceName](Device* device) {
            return device->getName() == deviceName;
            });
        if (it == devices.end()) {
            cout << "Device not found.\n";
            return;
        }
        Device* selectedDevice = *it;

        cout << "\nDevice: " << selectedDevice->getName()
            << " | Type: " << selectedDevice->getType()
            << " | Current Connection Status: "
            << (selectedDevice->CheckConnection() ? "Connected" : "Network Failure")
            << "\n";

        char toggleChoice;
        cout << "\nDo you want to toggle the connection status? (y/n): ";
        cin >> toggleChoice;

        if (toggleChoice == 'y' || toggleChoice == 'Y') {
            selectedDevice->toggleConnection();
        }
        else {
            cout << "No changes made to the connection status.\n";
        }
    }
    else if (all) {
        cout << "\nSelect a room to toggle connection status for all devices:\n";
        if (rooms.empty()) {
            cout << "No rooms available.\n";
            return;
        }

        for (size_t i = 0; i < rooms.size(); ++i) {
            cout << i + 1 << ". " << rooms[i]->getName() << "\n";
        }

        int roomChoice;
        cout << "Enter the room number: ";
        cin >> roomChoice;

        if (roomChoice < 1 || roomChoice > static_cast<int>(rooms.size())) {
            cout << INVALID_INPUT;
            return;
        }
        Room* selectedRoom = rooms[roomChoice - 1];
        vector<Device*> devicesInRoom = selectedRoom->getDevices();

        if (devicesInRoom.empty()) {
            cout << "No devices in this room to toggle connection status.\n";
            return;
        }
        bool allDevicesActive = true;
        for (auto& device : devicesInRoom) {
            if (!device->isActive()) {
                allDevicesActive = false;
                break;
            }
        }

        if (!allDevicesActive) {
            cout << "One or more devices are not active. Cannot change the connection status for all devices.\n";
            return;
        }

        char toggleChoice;
        cout << "\nDo you want to toggle the connection status for all devices in room \""
            << selectedRoom->getName() << "\"? (y/n): ";
        cin >> toggleChoice;

        if (toggleChoice == 'y' || toggleChoice == 'Y') {
            for (auto& device : devicesInRoom) {
                device->toggleConnection();
            }
        }
        else {
            cout << "No changes made to the connection status for devices in room \""
                << selectedRoom->getName() << "\".\n";
        }
    }
    else {
        cout << INVALID_INPUT;
    }
}



void showConnectionStatus(vector<Device*>& devices, vector<Room*>& rooms) {
    int choice = 0;
    while (true) {
        cout << "\n--- Device Connection Status ---\n";
        vector<Device*> activeDevices;

        for (const auto& device : devices) {
            if (device->isActive()) {
                activeDevices.push_back(device);
            }
        }

        if (!activeDevices.empty()) {
            for (const auto& device : activeDevices) {
                cout << "Device: " << device->getName()
                    << " | Type: " << device->getType()
                    << " | Connection Status: "
                    << (device->CheckConnection() ? "Connected" : "Disconnected")
                    << "\n";
            }

            cout << "\n1. Change Device Connection\n";
            cout << "2. Back\n";
            cout << "Please choose an option: ";
            cin >> choice;
            cin.ignore();

            if (choice == 1) {
                changeDeviceConnection(rooms, devices, true, false);
            }
            else if (choice == 2) {
                break;
            }
            else {
                cout << INVALID_INPUT;
                return;
            }
        }
        else {
            cout << "No active devices or all devices are disconnected.\n";
            break;
        }
    }
}
