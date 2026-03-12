#include <Arduino.h>

#include "UserManager.h"
#include "WebManager.h"
#include "constants.h"
#include "env.h"

UserManager* userManager;

// Instancia usando as constantes do arquivo Env.h
WebManager* webManager;

void setup() {
  userManager = new UserManager();
  webManager = new WebManager(AP_SSID, AP_PASSWORD, userManager);

  Serial.begin(115200);
  delay(2000);

  neopixelWrite(LED_PIN, 0, 50, 0);
  delay(500);
  neopixelWrite(LED_PIN, 0, 0, 0);

  Serial.println("\n--- EspSmartGate Iniciando ---");

  webManager->begin();
}

void loop() { delay(100); }