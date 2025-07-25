# Smart-room-automation-system-project-in-TinkerCAD
# 🏠 Smart Room Automation System Using Arduino

This Arduino-based **Smart Room Automation System** dynamically manages your room environment using sensors and actuators. It performs real-time temperature monitoring, automatic door operation, fan and AC indicator control, and issues high-temperature warnings using a buzzer and LCD display.

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

### Brightness Control (when AC is off):
- If room is dark (LDR < 600), gradually **increase** AC LED brightness.
- If room is bright (LDR ≥ 600), **decrease** brightness.
- Brightness range: `0–255` in steps of `10`.

---

## 🔌 Pin Configuration

| Pin | Connected To             |
|-----|--------------------------|
| A0  | LM35 Temperature Sensor  |
| A1  | LDR Sensor               |
| 2-5 | LCD (D7 to D4)           |
| 6   | AC LED (PWM)             |
| 7   | Fan                      |
| 8   | Buzzer                   |
| 9   | Servo Motor              |
| 11  | LCD EN                   |
| 12  | LCD RS                   |

---

## 💻 Code Highlights

- **Servo Movement Function:** Smooth door transitions
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

- **Temperature Calculation:**
```cpp
float voltage = analogRead(tempPin) * 5.0 / 1023.0;
temperatureC = (voltage - 0.5) * 100.0;
```

- **Buzzer Trigger Logic:**
```cpp
if (temperatureC > 30.0 && !buzzerTriggered) {
  buzzerTriggered = true;
  digitalWrite(buzzerPin, HIGH);
  buzzerStartTime = millis();
}
if (buzzerOn && millis() - buzzerStartTime >= 3000) {
  digitalWrite(buzzerPin, LOW);
}
```

---

## 📟 Sample LCD Display

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
- Connect all components to your Arduino board as per the pin layout.
- Power your Arduino via USB or external power source.

### 2. Uploading the Code
- Open Arduino IDE.
- Install `LiquidCrystal` and `Servo` libraries (usually preinstalled).
- Upload the sketch to the board.

### 3. Testing
- Use a lighter/heater to test LM35 response.
- Cover/uncover the LDR to test LED dimming.
- Observe LCD and Serial Monitor.

---

## 🎥 Demo Video (Optional)

> Embed a demo video or upload GIFs/images here.

---

## 🔧 Possible Upgrades

- WiFi/Bluetooth connectivity (e.g., ESP8266)
- DHT11 sensor for both Temp & Humidity
- Real-time clock (RTC) module for scheduling
- Mobile app integration
- Voice or gesture control
- Firebase or cloud logging

---

## 👨‍💻 Developed By

**TEAM SAM**

- 👨‍💻 Arduino Programming: [Your Name]
- 📐 Circuit Design: [Team Member]
- 💡 Idea & Logic: [Team Member]

> Proudly developed at KUET – Bangladesh 🇧🇩

---

## 📃 License

MIT License. Free to use, share, and improve.
