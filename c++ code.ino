#include <Servo.h>
#include <LiquidCrystal.h>

Servo doorServo;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Pin definitions
const int tempPin = A0;
const int ldrPin = A1;
const int acLed = 6;
const int servoPin = 9;
const int buzzerPin = 8;
const int fanPin = 7;

// Thresholds and variables
float temperatureC;
int tempRounded;
const int ldrThreshold = 600;
int brightness = 0;
const int maxBrightness = 255;
const int brightnessStep = 10;

// State variables
bool acIsOn = false;
bool buzzerOn = false;
bool buzzerTriggered = false;
unsigned long buzzerStartTime = 0;
int servoPos = 0;

void setup() {
  Serial.begin(9600);
  pinMode(acLed, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);
  digitalWrite(fanPin, LOW);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Smart Room");
  lcd.setCursor(0, 1);
  lcd.print("Automation");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("by TEAM SAM");
  delay(2000);
  lcd.clear();

  analogWrite(acLed, 0);

  doorServo.attach(servoPin);
  servoPos = 0;
  doorServo.write(servoPos); // Door open initially
}

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
  servoPos = toAngle;
}

void loop() {
  // Read sensors
  int tempVal = analogRead(tempPin);
  float voltage = tempVal * 5.0 / 1023.0;
  temperatureC = (voltage - 0.5) * 100.0;
  tempRounded = round(temperatureC);  // used for display
  int ldrVal = analogRead(ldrPin);

  // Display temperature
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(temperatureC, 1);
  lcd.print(" C    ");

  Serial.print("TempRounded: ");
  Serial.print(tempRounded);
  Serial.print(" | ServoPos: ");
  Serial.println(servoPos);

  // ==== DOOR CONTROL ====
  if (temperatureC <= 10.0) {
    if (servoPos != 90) {
      Serial.println("Door CLOSED (temp <= 10)");
      moveServoSmooth(servoPos, 90);
    }
  }
  else if (temperatureC > 10.0 && temperatureC < 24.0) {
    if (servoPos != 0) {
      Serial.println("Door OPEN (10 < temp < 24)");
      moveServoSmooth(servoPos, 0);
    }
  }
  else if (temperatureC >= 24.0 && temperatureC <= 30.0) {
    if (servoPos != 90) {
      Serial.println("Door CLOSED (24 <= temp <= 30)");
      moveServoSmooth(servoPos, 90);
    }
  }
  else if (temperatureC > 30.0) {
    if (servoPos != 0) {
      Serial.println("Door OPEN (temp > 30)");
      moveServoSmooth(servoPos, 0);
    }
  }

  // ==== LCD MESSAGE CONTROL ====
  lcd.setCursor(0, 1);

  if (temperatureC <= 10.0) {
    lcd.print("AC OFF DOOR OFF ");
  }
  else if (temperatureC > 10.0 && temperatureC < 24.0) {
    lcd.print("AC OFF DOOR ON  ");
  }
  else if (temperatureC >= 24.0 && temperatureC <= 30.0) {
    lcd.print("AC ON  DOOR OFF ");
  }
  else if (temperatureC > 30.0) {
    lcd.print("AC ERROR DOOR ON");
  }

  // ==== LED (AC) CONTROL ====
  if (tempRounded >= 24 && tempRounded <= 30) {
    if (!acIsOn) {
      Serial.println("AC ON (24<=temp<=30)");
      acIsOn = true;
      digitalWrite(buzzerPin, HIGH);
      delay(200);
      digitalWrite(buzzerPin, LOW);
    }
    brightness = maxBrightness;
    analogWrite(acLed, brightness);
  }
  else {
    if (acIsOn) {
      Serial.println("AC OFF");
      acIsOn = false;
      analogWrite(acLed, 0);
    }
    if (ldrVal < ldrThreshold) {
      brightness += brightnessStep;
      if (brightness > maxBrightness) brightness = maxBrightness;
    } else {
      brightness -= brightnessStep;
      if (brightness < 0) brightness = 0;
    }
    analogWrite(acLed, brightness);
  }

  // ==== BUZZER CONTROL (Temp > 30 triggers 3s buzz once) ====
  if (temperatureC > 30.0) {
    if (!buzzerTriggered) {
      buzzerTriggered = true;
      buzzerOn = true;
      buzzerStartTime = millis();
      digitalWrite(buzzerPin, HIGH);
      Serial.println("Buzzer ON for 3 seconds");
    }

    if (buzzerOn && (millis() - buzzerStartTime >= 3000)) {
      digitalWrite(buzzerPin, LOW);
      buzzerOn = false;
      Serial.println("Buzzer OFF");
    }
  }
  else {
    buzzerTriggered = false;
    digitalWrite(buzzerPin, LOW);
    buzzerOn = false;
  }

  // ==== FAN CONTROL ====
  if ((temperatureC >= 18.0 && temperatureC < 24.0) || temperatureC > 30.0) {
    digitalWrite(fanPin, HIGH);
  } else {
    digitalWrite(fanPin, LOW);
  }

  delay(200);
}
