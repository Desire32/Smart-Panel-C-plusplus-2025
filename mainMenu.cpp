#include <iostream>
#include <vector>
#include <string>

#include "SmartHome.h"
#include "backend.h"
#include "Devices.h"
#include "Room.h"

using namespace std;

/////////////////////
// main_menu.cpp, a smart control panel file, consists of all functionality of the panel, showing the main menu for the user with
// all functions
////////////////////


void main_menu(vector<Device*>& devices, vector<Room*>& rooms) {
    while (true) {
        cout << "\n--- Main Menu ---\n";
        cout << "Devices:\n";
        cout << "1. Show Devices\n";
        cout << "2. Change Device Settings\n";
        cout << "3. Show Devices Status\n";
        cout << "4. Show Devices Connection Status\n";
        cout << "5. Create Device\n";
        cout << "6. Delete Device\n";

        cout << "\nRooms:\n";
        cout << "7. Create Room\n";
        cout << "8. Show Rooms\n";
        cout << "9. Toggle Network Connection Status (Activate/Deactivate All)\n";
        cout << "10. Toggle Plugged Connection Status (Activate/Deactivate All)\n";
        cout << "11. Move Device to Another Room\n";

        cout << "\n12. Exit Program\n";
        cout << "Select an option: ";

        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }
        cin.ignore();

        switch (choice) {
        case 1: {
            showDevices(devices);
            break;
        }
        case 2: {
            changeDeviceSettings(devices);
            break;
        }
        case 3: {
            showWorkingStatus(devices);
            break;
        }
        case 4: {
            showConnectionStatus(devices, rooms);
            break;
        }
        case 5: {
            createDevice(devices, rooms);
            break;
        }
        case 6: {
            deleteDevice(devices, rooms);
            break;
        }
        case 7: {
            roomCreate(rooms);
            break;
        }
        case 8: {
            showRooms(rooms);
            break;
        }
        case 9: {
            changeDeviceConnection(rooms,devices,false,true);
            break;
        }
        case 10: {
            toggleAllDevicesStatus(rooms);
            break;
        }
        case 11: {
            moveDevice(rooms, devices);
            break;
        }
        case 12: {
            cout << "Exiting program...\n";
            return;
        }
        default:
            cout << "Invalid choice! Please select again.\n";
        }
    }
}