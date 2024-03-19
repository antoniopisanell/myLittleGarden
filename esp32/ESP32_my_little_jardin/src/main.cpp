#include <Arduino.h>

// ESP32 UDP chat program

#include <WiFi.h>
#include <WiFiUdp.h>

#include "config.h"

// SOURCE: https://forum.arduino.cc/t/esp32-s3-softap-connect-and-receive-data-with-python/1138978/2

// network SSID (network name). and network password.
// char ssid[] = "some ssid";
// char pass[] = "some secret";

// UDP information
unsigned int localPort = 10000;   // local port to listen on
unsigned int remotePort = 10000;  // remote port to transmiit too
WiFiUDP udp;

IPAddress remoteIP(172,20,10,7);;  // IP will be entered as text

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
}

void loop() {
  udp.begin(localPort);
  char text[100] = { 0 };
  sprintf(text, "Umidity: %d, Temperature: %d, Light: %d", getMockUmidityPercentage(), getMockTemperature(), getMockLight());
  Serial.print("Transmitting to ");
  displayIPaddress(remoteIP, remotePort);
  Serial.println(text);
  udp.beginPacket(remoteIP, remotePort);  // transmit datagram
  udp.print(text);
  udp.endPacket();
  delay(1000);
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