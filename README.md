# Fire Fighting Robot

Welcome to the Fire Fighting Robot project repository! This project involves the development of an autonomous robot capable of detecting and extinguishing fires. The robot is controlled by an Arduino microcontroller and utilizes a custom Android application for remote control and command transmission.

## Project Overview

The Fire Fighting Robot is designed to autonomously navigate an environment, detect fires using sensors, and extinguish them using a water pump or similar mechanism. The robot can also be controlled manually via a Bluetooth-enabled Android application.

## Repository Contents

1. **Arduino Code**: Contains the firmware for the Arduino microcontroller responsible for controlling the robot's movements, fire detection, and extinguishing mechanisms.
2. **Android Application**: A fully functional Android app that communicates with the Arduino via Bluetooth, allowing users to send commands and control the robot remotely.

## Arduino Code

The Arduino code is responsible for:
- Reading data from fire detection sensors (e.g., flame sensors).
- Controlling the robot's motors for navigation.
- Activating the fire extinguishing mechanism (e.g., water pump).
- Communicating with the Android app via Bluetooth.

### Dependencies
- Arduino IDE
- AFMotor Library (for motor control)
- SoftwareSerial Library (for Bluetooth communication)

### How to Use
1. Upload the provided Arduino code to your microcontroller.
2. Ensure all sensors and actuators are properly connected.
3. Power on the robot and pair it with the Android app.

## Android Application

The Android app is designed to:
- Establish a Bluetooth connection with the Arduino.
- Send commands to control the robot's movements.
- Receive real-time data from the robot (e.g., fire detection status).

### Features
- **Manual Control Mode**: Allows users to control the robot's movements using on-screen buttons.
- **Autonomous Mode**: Enables the robot to operate independently, detecting and extinguishing fires without user intervention.
- **Status Updates**: Displays real-time information about the robot's status, such as fire detection and battery level.

### How to Use
1. Install the APK file on your Android device.
2. Pair your device with the robot's Bluetooth module.
3. Open the app and connect to the robot.
4. Use the interface to control the robot or switch to autonomous mode.

## Hardware Components
- Arduino Uno or similar microcontroller
- Flame sensors
- DC motors with wheels
- L298N Motor Driver
- Water pump
- HC-05 Bluetooth module
- Power supply (e.g., batteries)

## Wiring Diagram
A detailed wiring diagram is included in the `docs` folder to help you connect all components correctly.

## Contributing
Contributions are welcome! If you'd like to contribute to this project, please fork the repository and submit a pull request with your changes.

## License
This project is licensed under the MIT License. See the `LICENSE` file for more details.

## Contact
For any questions or suggestions, feel free to reach out to me via [GitHub Issues](https://github.com/yourusername/fire-fighting-robot/issues) or email me at [your-email@example.com](mailto:your-email@example.com).

---

Thank you for checking out the Fire Fighting Robot project! We hope you find it useful and inspiring for your own robotics endeavors.
