# Home Automation with ESP32

This project demonstrates a cost-effective and practical approach to home automation with a focus on electrical safety. It integrates remote control, sensor monitoring, and safety features using an ESP32 microcontroller.

## Overview

This project demonstrates a cost-effective and practical approach to home automation with a focus on electrical safety. Using the ESP32 microcontroller, the system integrates:

1. **Remote Control:** via the Blynk cloud platform and touch sensors.
2. **Sensor Monitoring:** using a voltage sensor (ZMPT101B) and a DHT11 sensor for temperature and humidity.
3. **Safety Features:** Automatically disabling relays when voltage is unsafe and activating a buzzer if the temperature exceeds 50°C.

The project not only meets academic requirements in electrical measurement and instrumentation but also lays the groundwork for further enhancement in smart home applications.

## Features

1. **Remote Control and Monitoring:**  
   Seamless integration with the Blynk cloud for remote device control and sensor monitoring.
2. **Real Time Data Acquisition:**  
   Continuous reading of voltage and temperature values using ZMPT101B and DHT11 sensors.
3. **Automated Safety Logic:**  
   - **Voltage Monitoring:** Automatically cuts off relays if the voltage is outside the safe operating range (1–190 V or above 240 V).  
   - **Temperature Check:** Activates a buzzer as an audible alert when the temperature exceeds 50°C.
4. **Touch Sensor Interface:**  
   Provides manual override to control devices with capacitive touch inputs.
5. **Modularity and Expandability:**  
   Easily integrate additional sensors or control outputs in future updates.

## Hardware Components

- **ESP32 Microcontroller:** The central processing unit with built-in WiFi connectivity.
- **2 SPDT Active Low Relays:** Used for remotely controlling household appliances.
- **ZMPT101B Voltage Sensor:** Measures the RMS voltage supplying the load.
- **DHT11 Sensor:** Provides ambient temperature and humidity readings.
- **Capacitive Touch Sensors:** For manual operation of relay toggling (already present in some pins of the ESP32).
- **Buzzer:** Provides an audible safety alert when the temperature exceeds the predefined threshold.
- **Solderless Breadboard and Wiring:** For prototyping and circuit assembly.

## Software Components

- **Arduino IDE:** The development environment for programming the ESP32.
- **Libraries Used:**
  - `WiFi.h` & `BlynkSimpleEsp32.h` for wireless communication and cloud integration.
  - `DHT.h` for interfacing with the DHT11 sensor.
  - `ZMPT101B.h` for reading voltage from the ZMPT101B sensor.
  - Blynk’s timer and network functions for synchronizing sensor data.
- **Blynk Cloud Platform:** For remote control and real-time monitoring via a smartphone app.

## Circuit Diagram & Wiring

While a detailed circuit diagram is not provided in this README, the basic connections are as follows:

1. **ESP32 to Relays:**
   - Digital pins control the active low relays (e.g., GPIO25 and GPIO26).
2. **ESP32 to Sensors:**
   - **ZMPT101B:** Connected to an analog input (configured with proper sensitivity adjustments).
   - **DHT11:** Connected to a designated digital pin (e.g., GPIO15).
3. **ESP32 to Buzzer:**
   - A digital output pin (e.g., GPIO27) is used to trigger the buzzer.

## Installation & Setup

1. **Clone the Repository**
2. **Install Arduino IDE:**  
   Download and install the [Arduino IDE](https://www.arduino.cc/en/software).
3. **Install Required Libraries:**  
   Within the Arduino IDE, install the following libraries from the Library Manager:
   - WiFi
   - Blynk
   - DHT sensor library (by Adafruit or similar)
   - ZMPT101B (or the appropriate library for your voltage sensor)
4. **Configure WiFi and Blynk Credentials**
5. **Upload the Code:**  
   Connect your ESP32 board to your computer and upload the sketch using the Arduino IDE.

## Usage

- **Remote Control:**  
  Once the ESP32 connects to your WiFi network, use the Blynk mobile app to monitor sensor readings and control the relays.
- **Manual Operation:**  
  Use the touch sensors on the ESP32-based setup to manually toggle the relays.
- **Safety Monitoring:**  
  The system continuously monitors voltage and temperature. If the voltage falls outside 1–190 V or exceeds 240 V, the relays are automatically shut off. If the temperature exceeds 50°C, the buzzer is activated.
- **Debugging:**  
  Open the Serial Monitor in the Arduino IDE (set to 115200 baud) to view sensor values, relay states, and safety alerts.

## Contributing

Contributions are welcome! If you have suggestions for improvements or additional features, please fork the repository, create a new branch, and submit a pull request. For significant changes, please open an issue first to discuss what you would like to change.

## Acknowledgements

- Special thanks to the developers of the ESP32 environment, Blynk platform, and the Arduino community for their comprehensive resources.
- Acknowledge your professors, mentors, and peers at Gati Shakti Vishwavidyalaya for their guidance and support throughout the project.
