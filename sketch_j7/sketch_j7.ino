#include <Wire.h>
#include "SparkFun_ENS160.h"
#include <Adafruit_AHTX0.h>

SparkFun_ENS160 myENS;
Adafruit_AHTX0 myAHT;

void setup() {
  Wire.begin();
  Serial.begin(115200);

  // Initialize ENS160 sensor
  if (!myENS.begin()) {
    Serial.println("Error initializing ENS160 sensor.");
    while (1);
  }

  // Initialize AHT21 sensor
  if (!myAHT.begin()) {
    Serial.println("Error initializing AHT sensor.");
    while (1);
  }

  // Set ENS160 operating mode
  if (myENS.setOperatingMode(SFE_ENS160_RESET))
    Serial.println("ENS160 ready.");

  delay(100);
  myENS.setOperatingMode(SFE_ENS160_STANDARD);
}

void loop() {
  // Read humidity and temperature from AHT21 sensor
  sensors_event_t humidity, temp;
  myAHT.getEvent(&humidity, &temp); // Populate humidity and temp with the AHT sensor's readings

  Serial.print("Temperature (°C): ");
  Serial.println(temp.temperature);

  Serial.print("Relative Humidity (%RH): ");
  Serial.println(humidity.relative_humidity);

  // Check if ENS160 data is ready
  if (myENS.checkDataStatus()) {
    // Read TVOC from ENS160 sensor and convert to mg/m3
    float tvocPPB = myENS.getTVOC();
    float tvocMgM3 = tvocPPB * 1.96e-3;

    Serial.print("Total Volatile Organic Compounds (TVOC) (mg/m³): ");
    Serial.println(tvocMgM3, 5); // Display TVOC with 5 decimal places

    // Read CO2 concentration from ENS160 sensor
    Serial.print("CO2 concentration (ppm): ");
    Serial.println(myENS.getECO2());

    // Read Air Quality Index from ENS160 sensor
    Serial.print("Air Quality Index: ");
    Serial.println(myENS.getAQI());
  } else {
    Serial.println("Error: ENS160 data not ready.");
    // Optional: Reset the sensor if necessary
    myENS.setOperatingMode(SFE_ENS160_RESET);
    delay(100);
    myENS.setOperatingMode(SFE_ENS160_STANDARD);
  }

  // Print a blank line to separate each set of readings
  Serial.println();

  delay(3000); // Wait for a short interval before reading data again
}
