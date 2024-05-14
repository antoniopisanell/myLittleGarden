#include <Arduino.h>

// ESP32 UDP chat program

#include <WiFi.h>
#include <WiFiUdp.h>

#include "config.h"

// #include <Adafruit_Sensor.h>
// #include <DHT.h>
// #include <DHT_U.h>

#define DHTPIN 4     // Digital pin connected to the DHT sensor 
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

// DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

// SOURCE: https://forum.arduino.cc/t/esp32-s3-softap-connect-and-receive-data-with-python/1138978/2

// network SSID (network name). and network password.
// char ssid[] = "some ssid";
// char pass[] = "some secret";

// UDP information
unsigned int localPort = 10000;   // local port to listen on
unsigned int remotePort = 10000;  // remote port to transmiit too
WiFiUDP udp;

IPAddress remoteIP(172,20,10,3);;  // IP will be entered as text
char ssid[] = "Antonio’s iPhone";
char pass[] = "1234567890";

// function prototypes
IPAddress getIPaddress(const char* prompt);
void displayIPaddress(const IPAddress address, unsigned int port);
int getMockUmidityPercentage();
int getMockTemperature();
int getMockLight();

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(1);
  delay(1000);
  Serial.println();
  Serial.println("ESP32 WiFi UDP chat - send UDP datagrams ");
  WiFi.mode(WIFI_STA);  // Connect to Wifi network.
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {  // Wait for connection
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nGateway IP address: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("Ethernet UDP started ");
  displayIPaddress(WiFi.localIP(), localPort);
  // Begin udp port
  udp.begin(localPort);
  Serial.print("Opening udp port ");
  Serial.println(localPort);
  // get remote IP address
  //remoteIP = getIPaddress("\nenter remote IP address (e.g. 192.168.1.176)? ");
  Serial.print("\nRemote ");
  displayIPaddress(remoteIP, remotePort);

  // Initialize device.
  // dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  // sensor_t sensor;
  // dht.temperature().getSensor(&sensor);
  // Serial.println(F("------------------------------------"));
  // Serial.println(F("Temperature Sensor"));
  // Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  // Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  // Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  // Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  // Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  // Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  // Serial.println(F("------------------------------------"));
  // // Print humidity sensor details.
  // dht.humidity().getSensor(&sensor);
  // Serial.println(F("Humidity Sensor"));
  // Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  // Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  // Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  // Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  // Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  // Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  // Serial.println(F("------------------------------------"));
  // // Set delay between sensor readings based on sensor details.
  // delayMS = sensor.min_delay / 1000;
}

void loop() {
  udp.begin(localPort);
  char text[100] = { 0 };
  sprintf(text, "Humidity: %d,Temperature: %d,Light: %d", getMockUmidityPercentage(), getMockTemperature(), getMockLight());
  Serial.print("Transmitting to ");
  displayIPaddress(remoteIP, remotePort);
  Serial.println(text);
  udp.beginPacket(remoteIP, remotePort);  // transmit datagram
  udp.print(text);
  udp.endPacket();
  delay(1000);

  // // Delay between measurements.
  // delay(delayMS);
  // // Get temperature event and print its value.
  // sensors_event_t event;
  // dht.temperature().getEvent(&event);
  // if (isnan(event.temperature)) {
  //   Serial.println(F("Error reading temperature!"));
  // }
  // else {
  //   Serial.print(F("Temperature: "));
  //   Serial.print(event.temperature);
  //   Serial.println(F("°C"));
  // }
  // // Get humidity event and print its value.
  // dht.humidity().getEvent(&event);
  // if (isnan(event.relative_humidity)) {
  //   Serial.println(F("Error reading humidity!"));
  // }
  // else {
  //   Serial.print(F("Humidity: "));
  //   Serial.print(event.relative_humidity);
  //   Serial.println(F("%"));
  // }
}

// read IP address from keyboard and check it
IPAddress getIPaddress(const char* prompt) {
  IPAddress ip;
  while (1) {  // read  IP (end with new line)
    Serial.print(prompt);
    while (Serial.available() == 0) delay(10);
    char text[40] = { 0 };
    Serial.readBytesUntil('\n', (char *)text, 40);
    //Serial.println(text);
    if (ip.fromString(text)) break;  // if IP OK break while
    Serial.println("\ninvalid IP try again");
  }
  return ip;
}

// print IPAdress and port
void displayIPaddress(const IPAddress address, unsigned int port) {
  Serial.print(" IP ");
  for (int i = 0; i < 4; i++) {
    Serial.print(address[i], DEC);
    if (i < 3) Serial.print(".");
  }
  Serial.print(" port ");
  Serial.println(port);
}

int getMockUmidityPercentage() {
  return random(0, 100);
}

int getMockTemperature() {
  return random(-10, 40);
}

int getMockLight() {
  return random(0, 100);
}