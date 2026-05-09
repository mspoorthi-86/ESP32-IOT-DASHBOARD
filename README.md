# IoT Web Dashboard using ESP32-C3 🌐

## 🎯 Project Overview
[cite_start]This project demonstrates a basic IoT (Internet of Things) ecosystem where an **ESP32-C3** acts as a local web server[cite: 132]. [cite_start]It serves a real-time dashboard to monitor environmental data (Temperature & Humidity) and allows remote control of a physical device via a relay module[cite: 133].

## 🛠 Hardware Requirements
* [cite_start]**Microcontroller:** ESP32-C3 (RISC-V Architecture)[cite: 135].
* [cite_start]**Sensor:** HW-507 (DHT11) Temperature & Humidity Sensor[cite: 136].
* [cite_start]**Actuator:** HW-482 Single Channel Relay[cite: 137].
* [cite_start]**Connectivity:** 2.4GHz Wi-Fi[cite: 138].

## 🔌 Connection Map

| Module | Pin Label | ESP32-C3 Pin |
| :--- | :--- | :--- |
| **HW-507 (DHT)** | S (Signal) | GPIO 4 |
| | + (VCC) | 5V / VBUS |
| | - (GND) | GND |
| **HW-482 (Relay)**| S (Signal) | GPIO 10 |
| | + (VCC) | 5V / VBUS |
| | - (GND) | GND |

## ⚙️ Software Features
* [cite_start]**Asynchronous Web Server:** Uses `ESPAsyncWebServer` for non-blocking client handling[cite: 142].
* [cite_start]**Live AJAX Updates:** The dashboard fetches sensor data every 2 seconds via the JavaScript Fetch API without a page refresh[cite: 143].
* [cite_start]**Responsive UI:** A mobile-friendly CSS dashboard for remote monitoring[cite: 144].

## 🚀 Setup Instructions
1. [cite_start]**Library Installation:** Install `ESPAsyncWebServer`, `AsyncTCP`, and the Adafruit `DHT` sensor library[cite: 147, 148].
2. [cite_start]**Configuration:** Update the `ssid` and `password` variables in the code to match your Wi-Fi[cite: 149].
3. [cite_start]**Deployment:** Upload the code via Arduino IDE using the **ESP32C3 Dev Module** board setting[cite: 150].
4. **Access:** Open the Serial Monitor (115200 baud) to find the **Local IP address**. [cite_start]Enter this IP into any web browser on the same network to view the dashboard[cite: 151].
