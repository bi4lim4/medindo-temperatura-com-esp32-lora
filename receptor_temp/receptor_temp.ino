#include <Wire.h>
#include <LoRa.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define LORA_SCK 5
#define LORA_MISO 19
#define LORA_MOSI 27
#define LORA_SS 18
#define LORA_RST 14
#define LORA_DI0 26

// Wi-Fi and ThingSpeak details
const char* ssid = "Nome da sua rede wifi";
const char* password = "senha da sua rede wifi";
String apiKey = "Api disponobilizada no site thingspeak";
const char* server = "http://api.thingspeak.com/update";

void setup() {
  Serial.begin(9600);

  // Initialize Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  // Initialize LoRa
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DI0);
  if (!LoRa.begin(915E6)) {  // Set frequency
    Serial.println("Starting LoRa failed!");
    while (1);
  }n
  Serial.println("LoRa initialized successfully!");
}

void loop() {
  // Check if there's a LoRa packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String receivedData = "";
    while (LoRa.available()) {
      receivedData += (char)LoRa.read();
    }
    Serial.print("Received temperature: ");
    Serial.println(receivedData);

    // Send data to ThingSpeak
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      String url = String(server) + "?api_key=" + String(apiKey) + "&field1=" + String(receivedData);
      http.begin(url);
      int httpCode = http.GET();
      if (httpCode > 0) {
        Serial.printf("ThingSpeak response: %d\n", httpCode);
      } else {
        Serial.printf("Error in sending request: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();
    }
    delay(10000);  // Delay between requests
  }
}