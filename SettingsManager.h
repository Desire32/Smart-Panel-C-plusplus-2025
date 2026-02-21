#pragma once

#include <iostream>
#include "SmartHome.h"

// SettingsManager.h, the class which imports settings for all devices
void changeSecurityCameraSettings(Security_Camera* camera);
void changeSmartLightSettings(Smart_Light* light);
void changeThermostatSettings(Thermostat* thermostat);
void changeSpeakerSettings(Speaker* speaker);

