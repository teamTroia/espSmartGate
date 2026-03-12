#include "WebManager.h"

#include <LittleFS.h>

#include "env.h"

// Inicializa o servidor na porta 80 e define as credenciais

WebManager::WebManager(const char* apSsid, const char* apPassword,
                       UserManager* usrMngr)
    : server(80) {
  this->ssid = apSsid;
  this->password = apPassword;
  this->userManager = usrMngr;
}

void WebManager::begin() {
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
      if (inputPassword == ADMIN_PASS) {
        request->send(LittleFS, "/users.html", "text/html");
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

  // Rota para a página de administração
  server.on("/admin", HTTP_GET, [](AsyncWebServerRequest* request) {
    // Add verificação de sessão posteriormente
    request->send(LittleFS, "/admin.html", "text/html");
  });

  // Rota para a página de usuários
  server.on("/users", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (!request->authenticate(ADMIN_USER, ADMIN_PASS)) {
      return request->requestAuthentication();
    }
    request->send(LittleFS, "/users.html", "text/html");
  });

  // Rota que retorna os usuarios
  server.on("/api/users", HTTP_GET, [this](AsyncWebServerRequest* request) {
    request->send(200, "application/json", userManager->getUsersJson());
  });

  // Recebe novo usuário e salva no arquivo
  server.on("/api/addUser", HTTP_POST, [this](AsyncWebServerRequest* request) {
    String name = "";
    String uid = "";

    // Capturamos os parâmetros diretamente no loop, sem depender de hasParam
    for (size_t i = 0; i < request->params(); i++) {
      const AsyncWebParameter* p = request->getParam(i);
      if (p->name() == "name") name = p->value();
      if (p->name() == "uid") uid = p->value();
    }

    // Validação simples: se as strings não estão vazias, prosseguimos
    if (name != "" && uid != "") {
      if (userManager->addUser(name, uid)) {
        request->send(200, "text/plain", "OK");
        Serial.printf("![Web] Sucesso: %s adicionado.\n", name.c_str());
      } else {
        request->send(500, "text/plain", "Erro ao salvar no JSON");
      }
    } else {
      request->send(400, "text/plain", "Parametros invalidos ou vazios");
      Serial.println("![Web] Erro: Requisicao mal formatada.");
    }
  });
  // Remove o usuário se for autorizado
  server.on("/api/removeUser", HTTP_POST,
            [this](AsyncWebServerRequest* request) {
              if (request->hasParam("uid", true)) {
                String uid = request->getParam("uid", true)->value();

                if (userManager->removeUser(uid)) {
                  request->send(200, "text/plain", "Removido");
                } else {
                  request->send(404, "text/plain", "Usuario nao encontrado");
                }
              } else {
                request->send(400, "text/plain", "UID faltando");
              }
            });
  server.begin();

  Serial.println("Servidor Web iniciado na porta 80.");
}