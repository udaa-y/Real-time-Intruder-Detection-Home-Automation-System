# Real-time-Intruder-Detection-Home-Automation-System

Overview:
This project is a security-based embedded system using the ESP32 microcontroller. It integrates an RFID reader (MFRC522) and a piezoelectric vibration sensor to build an intelligent access and intrusion detection system. The device connects to Wi-Fi and communicates via the serial port. When unauthorized vibration is detected, it sends a custom trigger ("trigger_webcam") over the serial interface, which can be used to activate external systems such as webcams or alert mechanisms. Additionally, it reads RFID tags and compares them to a pre-configured authorized UID to grant or deny access.

Key Features:

Uses a piezoelectric sensor to detect vibrations or intrusions.
Employs an RFID reader (MFRC522) to identify authorized users.
Wi-Fi-enabled (connects using SSID and password).
Sends real-time messages over serial (e.g., to trigger webcam capture).
Provides access logs via Serial Monitor (displays UID, access status).
Customizable for security applications like door locks or surveillance systems.

Required Hardware:

ESP32 Board
Piezoelectric Sensor
MFRC522 RFID Reader
RFID Tag/Card
Jumper Wires, Breadboard

Working Methodology:

This project is a WiFi-enabled smart security system built using an ESP32 microcontroller, an RFID reader (MFRC522), and a piezoelectric sensor for intrusion detection. The system connects to a WiFi network and continuously monitors for two types of events: unauthorized physical intrusions and unauthorized RFID tag scans. If the piezo sensor detects vibrations above a defined threshold (indicating possible intrusion), the ESP32 sends a predefined serial message (trigger_webcam) that can be used by an external Python script or system to trigger actions such as capturing webcam footage. Simultaneously, the system uses the MFRC522 RFID module to read RFID tags and compare them against a predefined authorized UID. If a match is found, access is granted; otherwise, access is denied. All interactions are displayed via the serial monitor, making it easy to observe system behavior in real time. The project includes essential features like a delay after detection to prevent multiple redundant triggers and is ideal for integrating into DIY home security systems. Future enhancements could include mobile notifications, cloud-based logging, or integration with a full security dashboard.
