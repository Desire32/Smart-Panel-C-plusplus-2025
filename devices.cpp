#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <limits>
#include <algorithm>

#include "SmartHome.h"
#include "Devices.h"
#include "backend.h"

////////////////////////////
// devices.cpp, this file holds functionality of all smart control panel, creating devices, deleting, showing, "the brain" file.
//////////////////////////
using namespace std;

// error constants
const string DEVICE_NOT_FOUND = "Error: Base device can't be found. Cannot create a device.\n";
const string INVALID_INPUT = "Invalid choice. Please try again.\n";

// created template to find device by a type (makes code cleaner)
template<typename T>
T* findBaseDevice(const vector<Device*>& devices, const string& type) {
    auto baseDevice = find_if(devices.begin(), devices.end(), [&type](Device* device) {
        return device->getType() == type;
        });
    if (baseDevice == devices.end()) {
        cout << "No base " << type << " found. Cannot create a new device.\n";
        return nullptr;
    }
    return static_cast<T*>(*baseDevice);
}


// default info about devices
void ViewInfo(Device* device) {
    map<string, string> deviceInfo = {
        {"Camera", "Security Camera: A surveillance device for home security."},
        {"Thermostat", "Thermostat: A device for maintaining and controlling home temperature."},
        {"Speaker", "Speakers: A smart audio device for high-quality sound."},
        {"Light", "Smart Light: A lighting device with adjustable brightness and color."}
    };

    auto it = deviceInfo.find(device->getType());
    if (it != deviceInfo.end()) {
        cout << it->second << endl;
    }
    else {
        cout << "Unknown Device: No additional information available.\n";
    }
}

// show the list of devices on the screen
void showDevices(const vector<Device*>& devices) {
    cout << "\n--- Devices in Smart Home ---\n";
    for (const auto& device : devices) {
        device->InteractionEvent();
    }
}


// a function to manipulate device settings
void changeDeviceSettings(vector<Device*>& devices) {
    cout << "Available devices:\n";
    showDevices(devices);
    string deviceName;
    cout << "\nEnter the name of the device you want to manage: ";
    getline(cin, deviceName);

    auto it = find_if(devices.begin(), devices.end(), [&deviceName](Device* device) {
        return device->getName() == deviceName;
        });
    if (it == devices.end()) {
        cout << "Device \"" << deviceName << "\" not found.\n";
        return;
    }
    Device* selectedDevice = *it;

    if (!selectedDevice->isActive()) {
        cout << "Device \"" << selectedDevice->getName() << "\" is not active. Please activate it before changing settings.\n";
        return;
    }
    int choice = 0;

    do {
        cout << "\nManaging " << selectedDevice->getName() << ":\n";
        cout << "1. Show Information\n";
        cout << "2. Change Settings\n";
        cout << "3. Back\n";
        cout << "Enter your choice: ";

        cin >> choice;
        cin.ignore();

        if (choice < 1 || choice > 3) {
            cout << INVALID_INPUT;
        }
        switch (choice) {
        case 1:
            ViewInfo(selectedDevice);
            break;
        case 2:
            if (selectedDevice->getType() == "Camera") {
                changeSecurityCameraSettings(static_cast<Security_Camera*>(selectedDevice));
            }
            else if (selectedDevice->getType() == "Light") {
                changeSmartLightSettings(static_cast<Smart_Light*>(selectedDevice));
            }
            else if (selectedDevice->getType() == "Thermostat") {
                changeThermostatSettings(static_cast<Thermostat*>(selectedDevice));
            }
            else if (selectedDevice->getType() == "Speaker") {
                changeSpeakerSettings(static_cast<Speaker*>(selectedDevice));
            }
            break;
        case 3:
            cout << "Returning to main menu...\n";
            break;
        }
    } while (choice != 3);
}

/////////////////////////////////////////////////////////////////////////////////////////
// a function in order to create a device, first user has to choose a type from the list, after error checks if everything goes successful,
// there's a menu given to choose a room for a device, there's always a default one, dining room
///////////////////////////////////////////////////////////////
void createDevice(vector<Device*>& devices, vector<Room*>& rooms) {
    cout << "\n--- Add a New Device ---\n";
    cout << "Available device types:\n";
    cout << "1. Security Camera\n";
    cout << "2. Smart Light\n";
    cout << "3. Thermostat\n";
    cout << "4. Speaker\n";

    int choice;
    cout << "Enter the number corresponding to the device type: ";
    while (true) {
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << INVALID_INPUT;
        }
        else if (choice < 1 || choice > 4) {
            cout << INVALID_INPUT;
        }
        else {
            break;
        }
    }

    cin.ignore();

    string newName;
    while (true) {
        cout << "Enter a unique name for the new device: ";
        getline(cin, newName);
        bool nameExists = false;
        for (auto device : devices) {
            if (device->getName() == newName) {
                nameExists = true;
                break;
            }
        }

        if (nameExists) {
            cout << "Error: Device with this name already exists. Enter a unique name.\n";
        }
        else if (newName.empty()) {
            cout << "Error: Device name can't be empty. Enter a valid name.\n";
        }
        else {
            break;
        }
    }

    // unique id for new elements
    int newId = devices.empty() ? 1 : devices.back()->getId() + 1;
    Device* newDevice = nullptr;

    switch (choice) {
    case 1: { // camera
        Security_Camera* baseCamera = findBaseDevice<Security_Camera>(devices, "Camera");
        if (baseCamera == nullptr) {
            cout << DEVICE_NOT_FOUND;
            return;
        }
        newDevice = new Security_Camera(newId, newName, baseCamera->getQuality(), baseCamera->getPower());
        break;
    }
    case 2: { // smart Light
        Smart_Light* baseLight = findBaseDevice<Smart_Light>(devices, "Smart Light");
        if (baseLight == nullptr) {
            cout << DEVICE_NOT_FOUND;
            return;
        }
        newDevice = new Smart_Light(newId, newName, baseLight->getBrightness(), baseLight->getColorType());
        break;
    }
    case 3: { // thermostat
        Thermostat* baseThermostat = findBaseDevice<Thermostat>(devices, "Thermostat");
        if (baseThermostat == nullptr) {
            cout << DEVICE_NOT_FOUND;
            return;
        }
        newDevice = new Thermostat(newId, newName, baseThermostat->getTemperature());
        break;
    }
    case 4: { // speaker
        Speaker* baseSpeaker = findBaseDevice<Speaker>(devices, "Speaker");
        if (baseSpeaker == nullptr) {
            cout << DEVICE_NOT_FOUND;
            return;
        }
        newDevice = new Speaker(newId, newName, baseSpeaker->getVolumeLevel());
        break;
    }
    }

    cout << "\n--- Select a Room to Add the Device ---\n";
    for (size_t i = 0; i < rooms.size(); ++i) {
        cout << i + 1 << ". " << rooms[i]->getName() << "\n";
    }
    int roomChoice;
    cout << "Enter your choice: ";
    while (true) {
        cin >> roomChoice;
        if (cin.fail() || roomChoice < 1 || roomChoice > static_cast<int>(rooms.size() + 1)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << INVALID_INPUT;
        }
        else {
            break;
        }
    }

    cin.ignore();

    if (roomChoice == static_cast<int>(rooms.size() + 1)) {
        Room* defaultRoom = nullptr;
        for (auto r : rooms) {
            if (r->getName() == "Dining Room") {
                defaultRoom = r;
                break;
            }
        }
        if (defaultRoom) {
            devices.push_back(newDevice);
            defaultRoom->addDevice(newDevice);
            cout << "Device \"" << newName << "\" created successfully with ID " << newId << " and added to the default room!\n";
        }
        else {
            cout << "No default room found. Device was not added.\n";
            delete newDevice; // clean up if no room is found
        }
    }
    else {
        Room* selectedRoom = rooms[roomChoice - 1];
        devices.push_back(newDevice);
        selectedRoom->addDevice(newDevice);
        cout << "Device \"" << newName << "\" created successfully with ID " << newId << " and added to room \"" << selectedRoom->getName() << "\"!\n";
    }
}

// delete a device from vector, since a device can't exist oustide of a room
void deleteDevice(vector<Device*>& devices, vector<Room*>& rooms) {
    cout << "Available devices:\n";
    showDevices(devices);

    string deviceName;
    cout << "\nEnter the name of the device you want to delete: ";
    getline(cin, deviceName);

    if (deviceName == "Camera" || deviceName == "Light" || deviceName == "Thermostat" || deviceName == "Speaker") {
        cout << "Error: This is a base device and cannot be deleted.\n";
        return;
    }

    auto it = find_if(devices.begin(), devices.end(), [&deviceName](Device* device) {
        return device->getName() == deviceName;
        });

    if (it == devices.end()) {
        cout << "Device \"" << deviceName << "\" not found.\n";
        return;
    }

    Device* deviceToDelete = *it;

    // remove the device from all rooms
    for (auto& room : rooms) {
        room->removeDevice(deviceToDelete);
    }

    char confirmation;
    while (true) {
        cout << "Are you sure you want to delete the device \"" << deviceToDelete->getName() << "\"? (y/n): ";
        cin >> confirmation;
        cin.ignore();

        if (confirmation == 'y' || confirmation == 'Y') {
            cout << "Deleting device \"" << deviceToDelete->getName() << "\"...\n";
            devices.erase(it);
            delete deviceToDelete;
            cout << "Device deleted successfully.\n";
            break;
        }
        else if (confirmation == 'n' || confirmation == 'N') {
            cout << "Deletion cancelled.\n";
            break;
        }
        else {
            cout << "Invalid input. Please enter 'y' or 'n'.\n";
        }
    }
}


void toggleAllDevicesStatus(vector<Room*>& rooms) {
    cout << "\n--- Toggle Devices Status in a Selected Room ---\n";
    if (rooms.empty()) {
        cout << "No rooms available.\n";
        return;
    }
    cout << "Select a room:\n";
    for (size_t i = 0; i < rooms.size(); ++i) {
        cout << i + 1 << ". " << rooms[i]->getName() << "\n";
    }
    size_t roomChoice;
    cout << "Enter the room number: ";
    cin >> roomChoice;

    if (roomChoice < 1 || roomChoice > rooms.size()) {
        cout << INVALID_INPUT;
        return;
    }

    Room* selectedRoom = rooms[roomChoice - 1];
    vector<Device*> devicesInRoom = selectedRoom->getDevices();

    if (devicesInRoom.empty()) {
        cout << "No devices in this room to toggle.\n";
        return;
    }
    cout << "\nDevices in room \"" << selectedRoom->getName() << "\":\n";
    for (size_t i = 0; i < devicesInRoom.size(); ++i) {
        cout << i + 1 << ". " << devicesInRoom[i]->getName() << " ("
            << devicesInRoom[i]->getType() << ") - "
            << (devicesInRoom[i]->isActive() ? "Active" : "Inactive") << "\n";
    }
    char choice;
    cout << "\nDo you want to switch the status of all devices in this room? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        for (auto& device : devicesInRoom) {
            if (device->isActive()) {
                device->Deactivate();
            }
            else {
                device->Activate();
            }
        }
    }
    else if (choice == 'n' || choice == 'N') {
        cout << "No changes were made.\n";
    }
    else {
        cout << INVALID_INPUT;
    }
}

