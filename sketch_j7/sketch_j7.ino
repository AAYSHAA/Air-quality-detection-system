#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <ScioSense_ENS160.h>

Adafruit_AHTX0 aht;
// ScioSense_ENS160 ens160(ENS160_I2CADDR_1); // Use the correct I2C address
ScioSense_ENS160 ens160(ENS160_I2CADDR_0);


void setup() {
  Serial.begin(9600);
  while (!Serial) {
    // Wait for serial connection
  }

  aht.begin();
  ens160.begin();

  Serial.println("ENS160 + AHT21 Sensor Readings:");
}

void loop() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp); // Populate temp and humidity objects with fresh data

  // Read ENS160 data
  float tvoc = ens160.geteCO2(); // Use geteCO2() instead of getCO2eq()
  float co2eq = ens160.geteCO2(); // Correct method for CO2eq
  float aqi = ens160.getAQI();

  // Correctly read temperature from AHT21
  float tempC = temp.temperature; // Temperature in Celsius

  // Print sensor data

  Serial.print("Temperature (°C): "); Serial.println(tempC);
  Serial.print("Humidity (%): "); Serial.println(humidity.relative_humidity);
  Serial.print("TVOC (ppb): "); Serial.println(tvoc);
  Serial.print("CO2eq (ppm): "); Serial.println(co2eq);
  Serial.print("Air Quality Index (AQI): "); Serial.println(aqi);
  Serial.print(" ");

  delay(2000); // Adjust delay here
}