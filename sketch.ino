/*
  PROJETO: Office Sense
  EVENTO: Global Solutions 2025 - O Futuro do Trabalho
  
  AUTORES:
  - Vinicius Alexanxre Aureliano Ribeiro - RM561606

  DESCRIÇÃO:
  Sistema de monitoramento de saúde e ambiente para home office utilizando Edge Computing.
  O código lê sensores, processa alertas locais (sem internet) e envia telemetria para nuvem.
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// Hardware
#define DHTPIN 15
#define DHTTYPE DHT22
#define POT_PIN 34
#define TRIG_PIN 5
#define ECHO_PIN 18
#define LED_PIN 2
#define BUZZ_PIN 4

// Rede e API
const char* ssid = "Wokwi-GUEST";
const char* pass = "";
const char* apiKey = "93YQ6104PRZGH6YC"; 
const char* server = "http://api.thingspeak.com";

DHT dht(DHTPIN, DHTTYPE);
unsigned long lastTime = 0;
const long interval = 15000;

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(POT_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZ_PIN, OUTPUT);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) delay(100);
  Serial.println("WiFi OK");
}

void loop() {
  // 1. Leitura de Sensores
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) { h = 0; t = 0; }

  int bpm = map(analogRead(POT_PIN), 0, 4095, 60, 150);

  digitalWrite(TRIG_PIN, LOW); delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long dist = pulseIn(ECHO_PIN, HIGH) * 0.0344 / 2;

  // 2. Edge Computing (Lógica Local)
  bool alerta = false;
  int tom = 0;

  if (bpm > 110) { alerta = true; tom = 1000; }        // Estresse
  else if (dist < 30) { alerta = true; tom = 500; }    // Ergonomia
  else if (t > 35 || h < 30) { alerta = true; tom = 1500; } // Ambiente

  digitalWrite(LED_PIN, alerta);
  if (alerta) tone(BUZZ_PIN, tom, 200);
  else noTone(BUZZ_PIN);

  // 3. Envio Cloud (HTTP)
  if (millis() - lastTime > interval) {
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      String url = String(server) + "/update?api_key=" + apiKey + 
                   "&field1=" + t + "&field2=" + h + 
                   "&field3=" + bpm + "&field4=" + dist;
      
      http.begin(url);
      int code = http.GET();
      Serial.printf("Envio: %d | T:%.1f H:%.1f BPM:%d D:%ld\n", code, t, h, bpm, dist);
      http.end();
    }
    lastTime = millis();
  }
  delay(100);
}