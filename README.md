# Projeto de Transmissão e Recepção de Temperatura com LoRa e ThingSpeak

Este projeto consiste em um sistema de transmissão e recepção de dados de temperatura utilizando módulos LoRa. O transmissor coleta dados de temperatura de um sensor DHT11 e os envia via LoRa para o receptor. O receptor, por sua vez, recebe os dados e os envia para a plataforma ThingSpeak para monitoramento e análise.

## Componentes Utilizados

- **Transmissor:**
  - Módulo LoRa
  - Sensor DHT11
  - Microcontrolador (ex: ESP32)

- **Receptor:**
  - Módulo LoRa
  - Microcontrolador (ex: ESP32)
  - Conexão Wi-Fi para enviar dados ao ThingSpeak

## Bibliotecas Necessárias

- **LoRa:** Para comunicação via LoRa.
- **WiFi:** Para conexão Wi-Fi no receptor.
- **HTTPClient:** Para enviar dados ao ThingSpeak.
- **DHT:** Para leitura do sensor DHT11.

## Estrutura do Projeto

- `transmissor_temp.ino`: Código para o dispositivo transmissor.
- `receptor_temp.ino`: Código para o dispositivo receptor.