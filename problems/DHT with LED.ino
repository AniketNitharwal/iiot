#include "DHT.h"

#define DHTPIN 32     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  //float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  //float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.println("%");
  Serial.print(F(" Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
  Serial.print(F(" Temperature: "));
  Serial.print(f);
  Serial.println(F("°F "));

  if (h > 60) {                 // threshold humidity
    digitalWrite(13, HIGH);
    Serial.println("LED ON (High Humidity)");
  } else {
    digitalWrite(13, LOW);
    Serial.println("LED OFF (Normal Humidity)");
  }

  Serial.println("----------------------");
}
 

