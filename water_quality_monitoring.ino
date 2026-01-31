#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Pin connections
const int turbidityPin = A0; // Sensor analog output to A0
const int buzzerPin = 8; // Buzzer to digital pin 8
const int ledPin = 7; // LED to digital pin 7
float voltage, turbidity;
// LCD setup (16x2 LCD, common I2C addresses: 0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
Serial.begin(9600);
pinMode(buzzerPin, OUTPUT);
pinMode(ledPin, OUTPUT);
// Initialize LCD
lcd.init();
lcd.backlight();
lcd.setCursor(0, 0);
lcd.print("Initializing...");
delay(2000);
// Test LCD
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("LCD Working");
Serial.println("LCD should display 'LCD Working'");
delay(2000);
lcd.clear();
}
void loop() {
// Read turbidity sensor
int sensorValue = analogRead(turbidityPin);
voltage = sensorValue * (5.0 / 1023.0);
turbidity = -1120.4 * voltage * voltage + 5742.3 * voltage - 4352.9;

// Prevent negative values
if (turbidity < 0) turbidity = 0;
// Print on Serial Monitor
Serial.print("Voltage: ");
Serial.print(voltage);
Serial.print(" V, Turbidity: ");
Serial.print(turbidity, 2);
Serial.println(" NTU");
// Display on LCD
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Turbidity: ");
lcd.print(turbidity, 2);
lcd.print("NTU");
// WHO safe drinking water threshold
const float turbidityThreshold = 5.0;
lcd.setCursor(0, 1);
if (turbidity > turbidityThreshold) {
lcd.print("Water: NOT SAFE");
digitalWrite(buzzerPin, HIGH);
digitalWrite(ledPin, HIGH);

} else {
lcd.print("Water: SAFE ");
digitalWrite(buzzerPin, LOW);
digitalWrite(ledPin, LOW);
}
delay(1000); // Update every second

}
