#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Servo lidServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int servoPin = 3;
const int trigPin = 9;
const int echoPin = 10;
const int incButton = 6;
const int decButton = 7;

bool lidOpen = false;
bool lastComboState = false;

float containerHeight = 30.0;
bool confirmed = false;
unsigned long lastAdjustTime = 0;
const unsigned long adjustTimeout = 10000;

float getStableDistance() {
  const int samples = 5;
  float sum = 0;

  for (int i = 0; i < samples; i++) {
    digitalWrite(trigPin, LOW); delayMicroseconds(2);
    digitalWrite(trigPin, HIGH); delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout
    float distance = duration * 0.034 / 2;
    sum += distance;
    delay(30);
  }

  return sum / samples;
}

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(incButton, INPUT_PULLUP);
  pinMode(decButton, INPUT_PULLUP);

  lidServo.attach(servoPin);
  lidServo.write(0);

  lcd.setCursor(0, 0);
  lcd.print("Welcome!");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(3000);
  lcd.clear();
  lastAdjustTime = millis();
}

void loop() {
  bool incPressed = digitalRead(incButton) == LOW;
  bool decPressed = digitalRead(decButton) == LOW;
  bool comboPressed = incPressed && decPressed;

  if (comboPressed && !lastComboState) {
    if (!lidOpen) {
      lidServo.attach(servoPin);
      lidServo.write(110);
      delay(500);
      lidServo.detach();
      lidOpen = true;
    } else {
      lidServo.attach(servoPin);
      lidServo.write(0);
      delay(500);
      lidServo.detach();
      lidOpen = false;
    }
  }
  lastComboState = comboPressed;

  if (!confirmed) {
    lcd.setCursor(0, 0);
    lcd.print("Set Height:      ");
    lcd.setCursor(0, 1);
    lcd.print(containerHeight, 1);
    lcd.print(" cm     ");

    if (incPressed && !decPressed) {
      containerHeight += 0.5;
      lastAdjustTime = millis();
      delay(200);
    }
    if (decPressed && !incPressed) {
      containerHeight -= 0.5;
      if (containerHeight < 0) containerHeight = 0;
      lastAdjustTime = millis();
      delay(200);
    }

    if (millis() - lastAdjustTime > adjustTimeout) {
      confirmed = true;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Height Set:");
      lcd.setCursor(0, 1);
      lcd.print(containerHeight, 1);
      lcd.print(" cm");
      delay(2000);
      lcd.clear();
    }
  } else {
    float distance = getStableDistance();
    Serial.print("Distance: ");
    Serial.println(distance);

    if (distance > 0) {
      float waterLevel = containerHeight - distance;
      if (waterLevel < 0) waterLevel = 0;

      static float lastLevel = -1;
      if (abs(waterLevel - lastLevel) > 1) {
        lastLevel = waterLevel;

        lcd.setCursor(0, 0);
        lcd.print("Water Level:     ");
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        lcd.print(waterLevel, 1);
        lcd.print("cm ");

        int percent = (int)((waterLevel / containerHeight) * 100);
        lcd.print(percent);
        lcd.print("% Full");
      }
    } else {
      lcd.setCursor(0, 0);
      lcd.print("Measuring...     ");
      lcd.setCursor(0, 1);
      lcd.print("Hold steady...   ");
    }
  }
}
