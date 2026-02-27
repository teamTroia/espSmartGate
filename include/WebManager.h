#ifndef WEB_MANAGER_H
#define WEB_MANAGER_H

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

class WebManager {
private:
    AsyncWebServer server;
    const char* ssid;
    const char* password;

public:
    // Construtor usando camelCase nos parâmetros
    WebManager(const char* apSsid, const char* apPassword);
    
    // Método de inicialização
    void begin();
};

#endif