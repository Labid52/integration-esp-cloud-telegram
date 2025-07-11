

# ESP32 Cloud Server and Telegram Bot Integration

## Project Description

This project demonstrates the integration of an **ESP32 microcontroller** with the **Arduino IoT Cloud** to control and monitor a system. The system is designed to interact with a **Telegram bot**, enabling communication between the cloud server and the user via Telegram. The project includes features such as:

* **Cloud Connectivity** using Arduino IoT Cloud.
* **Control and Monitoring** through a **Telegram Bot**.
* **Sensor Data Management** (e.g., distance, throughput, RSSI).
* **Cloud Publishing** for continuous updates on sensor data.

This project provides a seamless connection between **IoT devices** (ESP32), cloud services, and **Telegram** for real-time interaction.

## Installation Instructions

### Prerequisites

1. **Arduino IDE** (with **ESP32 support** installed).

   * Install the **ESP32 Board** in the Arduino IDE through **Board Manager**.
   * Install the **Arduino IoT Cloud Library** for cloud services integration.

2. **Create an Arduino IoT Cloud Account**:

   * Visit [Arduino IoT Cloud](https://create.arduino.cc/iot) and create an account.
   * Set up a device (ESP32) on your account and generate the necessary credentials (device key).

3. **Telegram Bot Setup**:

   * Create a **Telegram bot** using [BotFather](https://core.telegram.org/bots#botfather).
   * Obtain the **Bot Token** and **Chat ID** to enable communication.

### Files Overview

* **arduino\_secrets.h**: This file contains **WiFi credentials**, **API keys**, and **private tokens** required to connect the ESP32 to WiFi and the Arduino IoT Cloud, as well as credentials for the **Telegram bot**.
* **thingProperties.h**: Contains the **IoT Cloud properties** that define how the ESP32 will interact with the cloud. It initializes sensor properties such as `IrState`, `distance`, `throughput`, and others, and also defines how data will be published to the cloud.
* **project\_main.ino**: The main Arduino sketch where the logic of the ESP32 is implemented. This file handles:

  * Connection to WiFi.
  * Integration with the Arduino IoT Cloud.
  * Reading sensor data and sending it to the cloud.
  * Handling Telegram bot commands to interact with the system.

### Steps

1. Clone or download the repository to your local machine.
2. Open **`project_main.ino`** in **Arduino IDE**.
3. Replace the credentials in **`arduino_secrets.h`** with your WiFi credentials, IoT Cloud details, and Telegram bot information.
4. **Upload the sketch** to your ESP32 board via the Arduino IDE.
5. **Monitor sensor data** in the **Arduino IoT Cloud** dashboard.
6. **Use Telegram bot** to send commands to the ESP32 or receive data updates.

### Libraries Needed

* **Arduino IoT Cloud** library: `#include <ArduinoIoTCloud.h>`
* **Arduino Connection Handler** library: `#include <Arduino_ConnectionHandler.h>`
* **Telegram Bot API library**: (optional, depending on your Telegram bot integration)

## Usage

Once the project is uploaded to the ESP32:

1. **Access the Arduino IoT Cloud** to monitor data and control IoT devices connected to the ESP32.
2. **Telegram Bot** will interact with the system:

   * Send commands to the bot to trigger actions on the ESP32.
   * Receive real-time data (e.g., sensor readings, status updates) from the ESP32 via Telegram.

### Telegram Bot Commands

* **`/status`**: Retrieve current status and sensor readings from the ESP32.
* **`/control [on/off]`**: Control a relay or other output devices connected to the ESP32.

## Conclusion

This project showcases how to combine **ESP32**, **Arduino IoT Cloud**, and a **Telegram bot** for seamless remote control and monitoring. The use of cloud services enables easy data storage and remote accessibility, while the Telegram bot provides a user-friendly interface for interaction.
<img width="1302" height="599" alt="image" src="https://github.com/user-attachments/assets/b44ffbb7-c3bc-4580-97b3-0755022124ce" />
<img width="1080" height="2049" alt="image" src="https://github.com/user-attachments/assets/e2967ab4-7a0f-4925-bbc5-6eb54bb05df7" />
<img width="1105" height="721" alt="image" src="https://github.com/user-attachments/assets/4efa1905-ff4d-44ec-8b0e-f2748c5c96f4" />



