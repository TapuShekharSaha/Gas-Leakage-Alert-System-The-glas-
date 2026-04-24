# Gas-Leakage-Alert-System-The-GLAS

## Overview
The Gas Leakage Alert System (GLAS) is an IoT-based safety system designed to detect LPG gas leakage in domestic and small-scale environments. The system continuously monitors gas concentration and provides immediate alerts when unsafe levels are detected.

Upon detecting leakage, the system:
- Activates an alarm (buzzer)
- Sends a notification message to the user’s mobile device

---

## Objective
- Detect LPG gas leakage in real time
- Provide instant alerts to users
- Prevent fire hazards and ensure safety

---

## Features
- Real-time gas detection
- Automatic buzzer alert system
- Mobile notification (SMS / IoT-based)
- Low-cost and efficient design
- Easy to deploy in homes and kitchens

---

## Components Used
| Component        | Description                          |
|-----------------|--------------------------------------|
| MQ-2 / MQ-5     | Gas Sensor for LPG detection         |
| Arduino/NodeMCU | Microcontroller                      |
| Buzzer          | Alarm system                         |
| GSM/Wi-Fi Module| For sending alerts                   |
| Power Supply    | System power source                  |

---

## Working Principle
1. The gas sensor continuously monitors LPG concentration in the air.
2. If the gas level exceeds a predefined threshold:
   - The microcontroller processes the signal
   - The buzzer is activated
   - A message is sent to the user's mobile device
3. The system continues monitoring until levels return to normal.

---

## System Architecture
