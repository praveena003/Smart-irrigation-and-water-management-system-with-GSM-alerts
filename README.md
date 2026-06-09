# Smart-irrigation-and-water-management-system-with-GSM-alerts
Developed a Smart Irrigation and Water Management System using LPC2129, SIM800C GSM module, and a soil moisture sensor. The system monitors soil conditions and allows users to remotely control irrigation through SMS commands.
# Smart Irrigation and Water Management System with GSM Alerts

## Overview

This project presents a Smart Irrigation and Water Management System using the LPC2129 ARM7 microcontroller, SIM800C GSM module, and YL-69 soil moisture sensor. The system monitors soil moisture conditions and sends GSM alerts to the user. Based on the received alert, the user can remotely control the irrigation motor through SMS commands, enabling efficient water usage and reducing manual intervention.

---

## Features

- Real-time soil moisture monitoring
- GSM-based SMS alert notifications
- Remote motor control using SMS commands
- 16x2 LCD display for status indication
- Water-efficient irrigation management
- Active LOW relay/LED control

---

## Hardware Components Used

- LPC2129 ARM7 Microcontroller
- SIM800C GSM/GPRS Module
- YL-69 Soil Moisture Sensor with LM393 Module
- 16x2 LCD Display
- Relay Module / LED
- Power Supply Unit

---

## Software Tools Used

- Embedded C
- Keil µVision
- Flash Magic

---

## Hardware Connections

| Component | LPC2129 Pin |
|-----------|-------------|
| GSM TXD | P0.1 (RXD0) |
| GSM RXD | P0.0 (TXD0) |
| Soil Sensor DO | P0.5 |
| LCD RS | P0.8 |
| LCD E | P0.9 |
| LCD D4 | P0.14 |
| LCD D5 | P0.15 |
| LCD D6 | P0.16 |
| LCD D7 | P0.17 |
| Relay/LED | P0.4 |

---

## Working Principle

1. The soil moisture sensor continuously monitors soil conditions.
2. When dry soil is detected, the system sends an SMS alert:
   ```
   SOIL DRY
   SEND a TO ON
   ```
3. The user replies with:
   ```
   a
   ```
4. The motor turns ON to start irrigation.
5. When wet soil is detected, the system sends an SMS alert:
   ```
   SOIL WET
   SEND b TO OFF
   ```
6. The user replies with:
   ```
   b
   ```
7. The motor turns OFF to stop irrigation.

---

## Project Structure

```
├── main.c
├── uart01.h
├── delay.h
├── lcddisp.h
└── README.md
```

---

## Future Enhancements

- Automatic motor control without user intervention
- Mobile application integration
- IoT-based cloud monitoring
- Soil moisture percentage display using ADC

---

## Technologies Used

- ARM7 LPC2129
- Embedded C Programming
- UART Communication
- GSM AT Commands
- LCD Interfacing
- Soil Moisture Sensing

---

## Author

**Praveena**

Embedded Systems Enthusiast | ARM7 | Embedded C | IoT Applications
