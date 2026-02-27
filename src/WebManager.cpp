#include "WebManager.h"
#include "env.h"
#include <LittleFS.h>

// Inicializa o servidor na porta 80 e define as credenciais
WebManager::WebManager(const char *apSsid, const char *apPassword) : server(80)
{
    this->ssid = apSsid;
    this->password = apPassword;
}

void WebManager::begin()
{
    if(!LittleFS.begin(true)){ // O 'true' tenta formatar se houver erro grave
        Serial.println("Erro ao montar o LittleFS!");
        return;
    }
    Serial.println("LittleFS montado com sucesso.");

    Serial.println("Iniciando modo Access Point (AP)...");

    // Configura o ESP32 como Access Point
    WiFi.softAP(ssid, password);

    IPAddress apIp = WiFi.softAPIP();
    Serial.print("Endereço IP do AP: ");
    Serial.println(apIp);

    //Rota padrao, cai direto na pagina de login
   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/index.html", "text/html");
    });

    //Rota de login
    server.on("/login", HTTP_POST, [](AsyncWebServerRequest *request){
        if(request->hasParam("adminPassword", true)) {
            String inputPassword = request->getParam("adminPassword", true)->value();
            
            // Compara com a senha definida no seu arquivo secreto Env.h
            if(inputPassword == AP_PASSWORD) { 
                request->send(200, "text/plain", "Success! System Unlocked.");
            } else {
                request->send(401, "text/plain", "Unauthorized: Incorrect Password.");
            }
        } else {
            request->send(400, "text/plain", "Bad Request: Password field missing.");
        }
    });

    // Rota para buscar o logo
    server.on("/icon.png", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/icon.png", "image/png");
    });
    // Inicia o servidor
    server.begin();
    Serial.println("Servidor Web Assíncrono iniciado na porta 80.");
}