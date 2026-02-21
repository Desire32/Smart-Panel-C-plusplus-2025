#include <algorithm>
#include <iostream>
#include "Room.h"
#include "backend.h"

using namespace std;

///////////////////////////////////////////////////////
// Room.cpp file implementation
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
//checks if the provided room name is valid
bool isValidRoomName(const string& name) {
    if (name.empty()) return false;

    for (char ch : name) {
        if (!isalnum(ch)) {
            return false;
        }
    }
    return true;
}


// initializes a Room object with a name and verbose mode (information about verbose in a class)
Room::Room(const string& name, bool verbose) : roomName(name), verboseMode(verbose) {}

void Room::addDevice(Device* device) {
    devicesInRoom.push_back(device);
}
void Room::removeDevice(Device* device) {
    auto it = find(devicesInRoom.begin(), devicesInRoom.end(), device);
    if (it != devicesInRoom.end()) {
        devicesInRoom.erase(it);
    }
}
void Room::showDevices() const {
    if (devicesInRoom.empty()) {
        cout << "No devices in room: " << roomName << "\n";
        return;
    }
    cout << "\n";
    for (const auto& device : devicesInRoom) {
        cout << "Type: " << device->getType() << "  Name: " << device->getName() << "\n";
    }
}


//returns the name of the room.
string Room::getName() const {
    return roomName;
}

//returns the list of devices in the room.
vector<Device*> Room::getDevices() const {
    return devicesInRoom;
}

//displays all available rooms and their devices.
void showRooms(const vector<Room*>& rooms) {
    cout << "Available Rooms:\n";
    if (rooms.empty()) {
        cout << "No rooms available.\n";
    }
    else {
        for (const auto& room : rooms) {
            cout << room->getName() << ": ";
            if (room->getDevices().empty()) {
                cout << "None\n";
            }
            else {
                room->showDevices();
            }
        }
    }
}

// move a device from one room to another one, if there's only one default room, nothing happens
void moveDevice(vector<Room*>& rooms, vector<Device*>& devices) {
    string deviceName;
    cout << "Enter device name to move: ";
    getline(cin, deviceName);

    Device* deviceToMove = nullptr;
    for (auto& device : devices) {
        if (device->getName() == deviceName) {
            deviceToMove = device;
            break;
        }
    }

    if (!deviceToMove) {
        cout << "Device not found.\n";
        return;
    }

    vector<Room*> availableRooms;
    for (auto& room : rooms) {
        bool isDeviceInRoom = false;
        for (auto& device : room->getDevices()) {
            if (device == deviceToMove) {
                isDeviceInRoom = true;
                break;
            }
        }
        if (!isDeviceInRoom) {
            availableRooms.push_back(room);
        }
    }

    if (availableRooms.empty()) {
        cout << "This device is already in all rooms.\n";
        return;
    }

    cout << "Select a room to move the device to:\n";
    for (size_t i = 0; i < availableRooms.size(); ++i) {
        cout << i + 1 << ". " << availableRooms[i]->getName() << endl;
    }

    int roomChoice;
    cout << "Enter the room number: ";
    cin >> roomChoice;
    cin.ignore();

    if (roomChoice < 1 || roomChoice > static_cast<int>(availableRooms.size())) {
        cout << "Invalid room selection.\n";
        return;
    }

    Room* targetRoom = availableRooms[roomChoice - 1];
    for (auto& room : rooms) {
        room->removeDevice(deviceToMove);
    }
    targetRoom->addDevice(deviceToMove);
    cout << "Device \"" << deviceName << "\" moved to room \"" << targetRoom->getName() << "\".\n";
}
void roomCreate(vector<Room*>& rooms) {
    string roomName;
    cout << "Enter room name (letters and digits only): ";
    getline(cin, roomName);

    if (!isValidRoomName(roomName)) {
        cout << "Room name must contain only letters and digits.\n";
        return;
    }
    Room* newRoom = new Room(roomName);
    rooms.push_back(newRoom);
    cout << "Room \"" << roomName << "\" created!\n";
}
