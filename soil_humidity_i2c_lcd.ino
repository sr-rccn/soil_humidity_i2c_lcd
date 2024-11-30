#define sensorPower 7
#define sensorPin A0

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define soilWet 200  // Define max value we consider soil 'wet'
#define soilDry 50   // Define min value we consider soil 'dry'

void setup() {
  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();


  pinMode(sensorPower, OUTPUT);

  // Initially keep the sensor OFF
  digitalWrite(sensorPower, LOW);

  Serial.begin(9600);
}

void loop() {
  //get the reading from the function below and print it
  int moisture = readSensor();


  Serial.print("Analog output: ");
  Serial.println(moisture);


  // Determine status of our soil
  if (moisture > soilDry) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(moisture);
    lcd.print("        :)");

    lcd.setCursor(0, 1);
    lcd.print("Wet");
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(moisture);
    lcd.print("        :(");

    lcd.setCursor(0, 1);
    lcd.print("Dry");
  }

  delay(1000);
}

//  This function returns the analog soil moisture measurement
int readSensor() {
  int sensorValue = analogRead(sensorPin);              // Read the analog value from sensor
  int outputValue = map(sensorValue, 0, 1023, 255, 0);  // map the 10-bit data to 8-bit data
  return outputValue;                                   // Return analog moisture value
}
