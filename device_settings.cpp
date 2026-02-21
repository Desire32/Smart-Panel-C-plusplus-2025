#include <iostream>
#include <vector>
#include <limits>
#include "Device.h"
#include "Devices.h"
#include "SmartHome.h"

///////
// device_settings.cpp, this file holds specific functionality for each device
///////


using namespace std;

// error constants
const string INVALID_INPUT = "Invalid choice. Please try again.\n";

// errors input checker
template<typename T>
bool getValidInput(T& input, const string& errorMessage) {
    cin >> input;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << errorMessage << endl;
        return false;
    }
    return true;
}


void changeSecurityCameraSettings(Security_Camera* camera) {
    int choice;
    do {
        cout << "\nSecurity Camera Settings:\n";
        cout << "1. Change Quality\n";
        cout << "2. Change Type of Power\n";
        cout << "3. Back\n";

        cout << "Enter your choice: ";
        if (!getValidInput(choice, "Invalid input. Please enter a number.")) {
            continue;
        }

        switch (choice) {
        case 1: {
            string new_quality;
            cout << "Choose from the list: 1080p, 720p, 2k, 4k\n";
            cout << "Enter new quality: ";
            if (!getValidInput(new_quality, "Invalid input. Please enter a right value")) {
                continue;
            }

            if (new_quality == "1080p" || new_quality == "720p" || new_quality == "2k" || new_quality == "4k") {
                camera->setQuality(new_quality);
                cout << "Quality updated to: " << camera->getQuality() << endl;
            }
            else {
                cout << "Error: Invalid quality choice. Please choose from 1080p, 720p, 2k, or 4k.\n";
            }
            break;
        }
        case 2: {
            string new_power;
            cout << "Choose type of power: Battery, Plugged, Battery+Solar\n";
            cout << "Enter new power type: ";
            if (!getValidInput(new_power, INVALID_INPUT)) {
                continue;
            }

            if (new_power == "Plugged" || new_power == "Battery" || new_power == "Battery+Solar") {
                camera->setPower(new_power);
                cout << "Power updated to: " << camera->getPower() << endl;
            }
            else {
                cout << INVALID_INPUT;
            }
            break;
        }
        case 3:
            cout << "Returning to the main menu...\n";
            break;
        default:
            cout << INVALID_INPUT;
            break;
        }
    } while (choice != 3);
}

void changeSmartLightSettings(Smart_Light* light) {
    int choice;
    do {
        cout << "\nSmart Light Settings:\n";
        cout << "1. Change Brightness\n";
        cout << "2. Change Color Type\n";
        cout << "3. Back\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << INVALID_INPUT;
            continue;
        }

        switch (choice) {
        case 1: {
            int32_t new_brightness;
            cout << "Enter new brightness (0 to 100): ";
            cin >> new_brightness;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << INVALID_INPUT;
            }
            else if (new_brightness >= 0 && new_brightness <= 100) {
                light->setBrightness(new_brightness);
                cout << "Brightness updated to: " << light->getBrightness() << endl;
            }
            else {
                cout << "Error: Brightness must be between 0 and 100.\n";
            }
            break;
        }
        case 2: {
            string new_color;
            cout << "Choose from the list: Warm White, Cool White, RGB\n";
            cout << "Enter new color type: ";

            cin.ignore();
            getline(cin, new_color);

            if (new_color == "Warm White" || new_color == "Cool White" || new_color == "RGB") {
                light->setColorType(new_color);
                cout << "Color updated to: " << light->getColorType() << endl;
            }
            else {
                cout << "Error: Invalid color choice. Please choose from the given options.\n";
            }
            break;
        }
        case 3:
            cout << "Returning to the main menu...\n";
            break;
        default:
            cout << INVALID_INPUT;
            break;
        }
    } while (choice != 3);
}

void changeThermostatSettings(Thermostat* thermostat) {
    int choice;
    do {
        cout << "\nThermostat Settings:\n";
        cout << "1. Change Temperature (0 to 30°C)\n";
        cout << "2. Back\n";
        cout << "Enter your choice: ";

        if (!getValidInput(choice, "Invalid input. Please enter a right value")) {
            continue;
        }

        switch (choice) {
        case 1: {
            double new_temperature;
            cout << "Enter new target temperature (0 to 30°C): ";
            if (!getValidInput(new_temperature, "Invalid input. Please enter a valid temperature.")) {
                continue;
            }

            if (new_temperature >= 0 && new_temperature <= 30) {
                thermostat->setTemperature(new_temperature);
                cout << "Temperature updated to: " << thermostat->getTemperature() << "°C\n";
            }
            else {
                cout << "Error: Temperature must be between 0 and 30°C.\n";
            }
            break;
        }
        case 2:
            cout << "Returning to the main menu...\n";
            break;
        default:
            cout << INVALID_INPUT;
            break;
        }
    } while (choice != 2);
}


void changeSpeakerSettings(Speaker* speaker) {
    int choice;
    do {
        cout << "\nSpeaker Settings:\n";
        cout << "1. Change Volume Level\n";
        cout << "2. Back\n";

        cout << "Enter your choice: ";
        if (!getValidInput(choice, INVALID_INPUT)) {
            continue;
        }

        switch (choice) {
        case 1: {
            int32_t new_volume;
            cout << "Enter new volume level (0 to 100): ";
            if (!getValidInput(new_volume, INVALID_INPUT)) {
                continue;
            }

            if (new_volume >= 0 && new_volume <= 100) {
                speaker->setVolumeLevel(new_volume);
                cout << "Volume updated to: " << speaker->getVolumeLevel() << endl;
            }
            else {
                cout << "Error: Volume must be between 0 and 100.\n";
            }
            break;
        }
        case 2:
            cout << "Returning to the main menu...\n";
            break;
        default:
            cout << INVALID_INPUT;
            break;
        }
    } while (choice != 2);
}