
#include <WiFi.h>
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
#include "DHT.h"

#define DHTPIN 21
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#define SECRET_SSID "OnePlus ( Ace )"		// replace MySSID with your WiFi network name
#define SECRET_PASS "qwerty12345"	// replace MyPassword with your WiFi password

#define SECRET_CH_ID 3263245			// replace 0000000 with your channel number
#define SECRET_WRITE_APIKEY "6AGR8T01GNQ3BZ7S"   // replace XYZ with your channel write API Key



char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

int number = 0;

void setup() {
  Serial.begin(115200);  //Initialize serial
  Serial.println(F("DHTxx test!"));

  dht.begin();
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {

  // Connect or reconnect to WiFi
 if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);

    while (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(ssid, pass);
        Serial.print(".");
        delay(5000);
    }

    Serial.println("\nConnected.");
}


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

  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  // pieces of information in a channel.  Here, we write to field 1.
  ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 2, h, myWriteAPIKey);
  
  
  delay(2000); // Wait 20 seconds to update the channel again
   Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.println("%");
  Serial.print(F(" Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
  Serial.print(F(" Temperature: "));
  Serial.print(f);
  Serial.println(F("°F "));
}
