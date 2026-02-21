#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <iostream>
#include <vector>
#include <string>

#include "Room.h"
#include "Devices.h"
#include "SmartHome.h"


using namespace std;

int main() {
    // initial devices as an example
    Security_Camera* camera_device = new Security_Camera(1, "Camera", "2k", "Battery");
    Thermostat* thermostat_device = new Thermostat(2, "Thermostat", 25);
    Speaker* speaker_device = new Speaker(3, "Speakers", 50);
    Smart_Light* light_device = new Smart_Light(4, "Light", 50, "Warm White");

    // vectors
    vector<Room*> rooms;
    vector<Device*> devices;

    // some room which is going to be as default place for devices
    Room* defaultRoom = new Room("Dining Room", false);
    rooms.push_back(defaultRoom);

    // to the devices
    devices.push_back(camera_device);
    devices.push_back(thermostat_device);
    devices.push_back(speaker_device);
    devices.push_back(light_device);

    // to the room
    defaultRoom->addDevice(camera_device);
    defaultRoom->addDevice(thermostat_device);
    defaultRoom->addDevice(speaker_device);
    defaultRoom->addDevice(light_device);

    // start
    main_menu(devices, rooms);

    // clear memory after we finished
    for (auto room : rooms) {
        delete room;
    }
    for (auto device : devices) {
        delete device;
    }

    _CrtDumpMemoryLeaks();
    return 0;
}
