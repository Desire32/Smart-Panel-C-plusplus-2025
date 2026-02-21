# Smart Panel, C++ (11,14)

The goal of the work was to develop a console-based smart home control system that would allow users to control various devices. Each device was represented by a class with a corresponding name, all of which inherited from a Device.h class.
Several class parents were created consisting of other classes, such as SettingsManager.h and SmartHome.h, which ensured that the code was organized and easy to import. 
The main menu is presented at the entrance, divided into "Devices" and "Rooms". The "Devices" section allows users to show sevices, change device settings, show different connection statuses, create and delete devices. All devices initially located in a default room.
The "Rooms" section allows users to create rooms, show rooms, turn on/turn off different connection statuses and move devices from one room to another.
