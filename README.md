# 🏠 Smart Room Automation System Using Arduino – TinkerCAD Project

This Arduino-based **Smart Room Automation System** dynamically manages your room environment using sensors and actuators. It performs real-time temperature monitoring, automatic door operation, fan and AC indicator control, and issues high-temperature warnings using a buzzer and LCD display.

🔗 **Live Tinkercad Simulation:**  
👉 [Click here to open simulation](https://www.tinkercad.com/things/3W6tHAb6bsD-smart-room-automation-system-?sharecode=9gMvSxfNsFJOKDTjLc7XW1A-RbudFWR5cnX_vT0V_d0)

---

## 📌 Project Overview

This system mimics a miniature **Smart Home Environment Controller**. It aims to:
- Automate responses to **temperature and light** changes.
- Improve **energy efficiency** (e.g., fan and AC control).
- Alert users about **critical conditions**.
- Offer a **user-friendly display** using an LCD and **smooth motion** through a servo motor.

---

## 🎯 Objectives

- 🔄 Automate door movement using a servo based on temperature.
- ❄️ Simulate AC control with a PWM LED based on temperature and light intensity.
- 🔊 Provide safety alerts through a buzzer when temperature exceeds safe limits.
- 🌀 Operate a fan in moderate or hot conditions.
- 📟 Display room conditions clearly on an LCD.
- 🛠️ Provide serial monitoring for debugging and system testing.

---

## 🧰 Hardware Components

| Component               | Description                         | Quantity |
|------------------------|-------------------------------------|----------|
| Arduino UNO            | Main microcontroller                | 1        |
| LM35 Temperature Sensor| Analog temperature sensor           | 1        |
| LDR (Photoresistor)    | Light sensor for ambient brightness | 1        |
| SG90 Servo Motor       | For door opening/closing            | 1        |
| 16x2 LCD Display       | For displaying temperature & status | 1        |
| Buzzer                 | For overheating alarm               | 1        |
| LED (AC Indicator)     | PWM brightness simulation           | 1        |
| DC Fan (simulated)     | Room ventilation                    | 1        |
| Resistors, Breadboard, Jumper Wires, Power Supply | Supporting components | As needed |

---

## 🧠 System Logic

### Temperature Zones:

| Temp Range (°C) | Action                                     | LCD Message             | Fan   | Servo (Door) | Buzzer |
|-----------------|--------------------------------------------|--------------------------|--------|---------------|--------|
| ≤ 10            | AC off, Door closed                        | `AC OFF DOOR OFF`        | ❌     | Closed (90°)  | ❌     |
| 10 < T < 24     | AC off, Door open, Fan on                  | `AC OFF DOOR ON`         | ✅     | Open (0°)     | ❌     |
| 24 ≤ T ≤ 30     | AC on (LED ON), Door closed                | `AC ON  DOOR OFF`        | ❌     | Closed (90°)  | ✅ (short beep) |
| > 30            | AC error, Door open, Fan on, 3s buzzer     | `AC ERROR DOOR ON`       | ✅     | Open (0°)     | ✅ (3 sec) |

---

## 💡 Brightness Control (LDR + PWM)

- If room is dark (`LDR < 600`): **Gradually increase** AC LED brightness.
- If room is bright: **Decrease** brightness.
- Brightness changes in steps of `10`, max value `255`.

---

## 🔌 Pin Configuration

| Arduino Pin | Connected To             |
|-------------|--------------------------|
| A0          | LM35 Temperature Sensor  |
| A1          | LDR Sensor               |
| 2–5         | LCD (D7 to D4)           |
| 6           | AC LED (PWM)             |
| 7           | Fan                      |
| 8           | Buzzer                   |
| 9           | Servo Motor              |
| 11          | LCD Enable (EN)          |
| 12          | LCD Register Select (RS) |

---

## 💻 Code Highlights

### 🧭 Servo Movement Function
```cpp
void moveServoSmooth(int fromAngle, int toAngle) {
  if (fromAngle < toAngle) {
    for (int pos = fromAngle; pos <= toAngle; pos++) {
      doorServo.write(pos);
      delay(15);
    }
  } else {
    for (int pos = fromAngle; pos >= toAngle; pos--) {
      doorServo.write(pos);
      delay(15);
    }
  }
}
```

### 🌡️ Temperature Reading Logic
```cpp
int tempVal = analogRead(tempPin);
float voltage = tempVal * 5.0 / 1023.0;
temperatureC = (voltage - 0.5) * 100.0;
```

### 🔊 Buzzer Alert Logic
```cpp
if (temperatureC > 30.0 && !buzzerTriggered) {
  buzzerTriggered = true;
  buzzerOn = true;
  buzzerStartTime = millis();
  digitalWrite(buzzerPin, HIGH);
}
if (buzzerOn && (millis() - buzzerStartTime >= 3000)) {
  digitalWrite(buzzerPin, LOW);
  buzzerOn = false;
}
```

---

## 📟 LCD Sample Output

```
Temp: 26.5 C
AC ON  DOOR OFF
```

```
Temp: 9.8 C
AC OFF DOOR OFF
```

---

## 🧪 How to Use

### 1. Wiring
- Follow the pin configuration table above.
- Ensure power supply is stable for servo motor movement.

### 2. Upload Code
- Open Arduino IDE.
- Load the `.ino` file.
- Upload to Arduino UNO.

### 3. Test & Simulate
- In Tinkercad, adjust LM35 temperature slider.
- Cover LDR sensor to simulate darkness.
- Observe fan, buzzer, door, LCD, and LED behavior.



## 🚀 Future Enhancements

- 📶 Add WiFi/Bluetooth control (ESP8266/HC-05)
- 📱 Android/iOS App Integration
- 🌐 Cloud logging with Firebase
- ⏰ Real-Time Clock (RTC) for timed events
- 🎤 Voice Control using Google Assistant/Alexa

---

## 👨‍💻 Developed By

**TEAM SAM**

- 👨‍💻 Arduino Programming: [Your Name]
- 📐 Circuit Design: [Team Member]
- 💡 Logic & Simulation: [Team Member]

> 🏫 KUET – Khulna University of Engineering & Technology  
> 🇧🇩 Department of Electrical & Electronic Engineering (EEE)

---

## 📄 License

This project is licensed under the MIT License – feel free to use, modify, and share!

---

