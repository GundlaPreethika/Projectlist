#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// Replace with your network credentials
char ssid[] = "your_SSID";
char pass[] = "your_PASSWORD";

// Replace with your Blynk Auth Token
char auth[] = "your_BLYNK_AUTH_TOKEN";

// DHT Sensor setup
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

// Soil moisture sensor setup
const int soilMoisturePin = A0;
int soilMoistureValue = 0;

void setup() {
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  dht.begin();
}

void loop() {
  Blynk.run();
  
  // Read humidity and temperature from DHT sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Read soil moisture value
  soilMoistureValue = analogRead(soilMoisturePin);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print values to Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" *C\t");
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoistureValue);

  // Send data to Blynk
  Blynk.virtualWrite(V1, temperature);
  Blynk.virtualWrite(V2, humidity);
  Blynk.virtualWrite(V3, soilMoistureValue);

  delay(2000);  // Delay for 2 seconds
}
