#include "WebManager.h"

#include <LittleFS.h>

#include "env.h"

// Inicializa o servidor na porta 80 e define as credenciais

WebManager::WebManager(const char* apSsid, const char* apPassword)
    : server(80) {
  this->ssid = apSsid;

  this->password = apPassword;
}

void WebManager::begin()

{
  if (!LittleFS.begin(true)) {  // O 'true' tenta formatar se houver erro grave

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

  // Rota padrao, cai direto na pagina de login
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(LittleFS, "/index.html", "text/html");
  });

  // Rota de login
  server.on("/login", HTTP_POST, [](AsyncWebServerRequest* request) {
    if (request->hasParam("adminPassword", true)) {
      String inputPassword = request->getParam("adminPassword", true)->value();
      if (inputPassword == AP_PASSWORD) {
        request->send(200, "text/plain", "Sucesso! Sistema desbloqueado.");
      } else {
        request->send(401, "text/plain", "Não autorizado: Senha incorreta.");
      }
    } else {
      request->send(400, "text/plain", "Erro: Campo de senha vazio.");
    }
  });

  // Rota para buscar o logo
  server.on("/icon.png", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(LittleFS, "/icon.png", "image/png");
  });

  server.begin();

  Serial.println("Servidor Web iniciado na porta 80.");
}