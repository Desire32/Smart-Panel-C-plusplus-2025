#pragma once

// backend functional, consisting of connection functions and main menu

#include <iostream>
#include <string>
#include <vector>
#include "Device.h"
#include "Room.h"

void showWorkingStatus(const vector<Device*>& devices);
void changeDeviceConnection(vector<Room*>& rooms, vector<Device*>& devices, bool single, bool all);
void showConnectionStatus(vector<Device*>& devices, vector<Room*>& rooms);

void main_menu(vector<Device*>& devices, vector<Room*>& rooms);
