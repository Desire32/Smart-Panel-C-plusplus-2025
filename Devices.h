#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Device.h"
#include "Room.h"
#include "backend.h"

// devices instances
void ViewInfo(Device* device);
void deleteDevice(vector<Device*>& devices, vector<Room*>& rooms);
void createDevice(vector<Device*>& devices, vector<Room*>& rooms);
void showDevices(const vector<Device*>& devices);
void changeDeviceSettings(vector<Device*>& devices);
void toggleAllDevicesStatus(vector<Room*>& rooms);
