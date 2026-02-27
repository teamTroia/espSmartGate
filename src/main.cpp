#include "../include/libs.h"
#include "../include/defines.h"

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Iniciando teste do LED RGB (WS2812)...");
}

void loop() {
  
  Serial.println("Cor: Vermelho");
  neopixelWrite(RGB_BUILTIN, 50, 0, 0); 
  delay(1000);

  Serial.println("Cor: Verde");
  neopixelWrite(RGB_BUILTIN, 0, 50, 0); 
  delay(1000);

  Serial.println("Cor: Azul");
  neopixelWrite(RGB_BUILTIN, 0, 0, 50); 
  delay(1000);

  Serial.println("Cor: Desligado");
  neopixelWrite(RGB_BUILTIN, 0, 0, 0); 
  delay(1000);
}