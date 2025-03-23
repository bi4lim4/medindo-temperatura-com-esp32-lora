#include <Wire.h>
#include <LoRa.h>
#include <DHT.h>

#define DHTPIN 13      // Define DHT sensor pin
#define DHTTYPE DHT11  // Define DHT type (DHT11 or DHT22)
DHT dht(DHTPIN, DHTTYPE);

#define LORA_SCK 5
#define LORA_MISO 19
#define LORA_MOSI 27
#define LORA_SS 18
#define LORA_RST 14
#define LORA_DI0 26

void setup() {
  Serial.begin(9600);
  dht.begin();

  // Initialize LoRa module
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DI0);
  if (!LoRa.begin(915E6)) {  // Set frequency (US = 915E6)
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa initialized successfully!");
}

void loop() {
  float temperature = dht.readTemperature();
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Serial.print("Sending temperature: ");
  Serial.println(temperature);

  // Start packet and send data
  LoRa.beginPacket();
  LoRa.print(temperature);
  LoRa.endPacket();

  delay(10000);  // Send data every 10 seconds
}