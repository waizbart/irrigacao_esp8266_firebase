#include <Wire.h>
#include "SSD1306Wire.h"

#define UMITY_SENSOR_PIN A0
#define MAX_ANALOG_OFFSET 340
#define RELE_PIN D4
  
SSD1306Wire  display(0x3c, D1, D2);

int leitura_percent, leitura;

void setup()
{
  pinMode(RELE_PIN, OUTPUT);
  
  Serial.begin(115200);
  display.init();
  display.flipScreenVertically();
}

void mostraUmidade(int value)
{
    display.clear();
    display.drawProgressBar(0, 32, 120, 10, value);
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_16);
    display.drawString(64, 15, "Umidade: " + String(value) + "%");
    display.display();
    delay(10);
}
void loop()
{
  leitura = analogRead(UMITY_SENSOR_PIN);
  leitura_percent = 100 - map(leitura, MAX_ANALOG_OFFSET, 1024, 0, 100);
  Serial.println(leitura_percent);
  if (leitura_percent < 10){
    Serial.println("Irrigando...");
    digitalWrite(RELE_PIN, HIGH);
  } else {
    digitalWrite(RELE_PIN, LOW);
  }

  mostraUmidade(leitura_percent);

  delay(1000);
}
