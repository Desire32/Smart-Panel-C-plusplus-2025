#pragma once

#include <string>
#include <vector>
#include "Device.h"

// Room.h class, consists of functions specifically for room, verbose was used in order to not show initial loading of models in the vector
class Room {
public:
    Room(const string& name, bool verbose = false);

    void addDevice(Device* device);
    void removeDevice(Device* device);
    void showDevices() const;
    vector<Device*> getDevices() const;
    string getName() const;

private:
    string roomName;
    vector<Device*> devicesInRoom;
    bool verboseMode;
};

void showRooms(const vector<Room*>& rooms);
void moveDevice(vector<Room*>& rooms, vector<Device*>& devices);
void roomCreate(vector<Room*>& rooms);
