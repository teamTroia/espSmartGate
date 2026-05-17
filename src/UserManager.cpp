#include "UserManager.h"

UserManager::UserManager() {}

bool UserManager::begin() {
  if (!LittleFS.begin()) {
    Serial.println("![UserManager] Erro ao iniciar LittleFS");
    return false;
  }

  if (!LittleFS.exists(filePath)) {
    File file = LittleFS.open(filePath, "w");
    if (file) {
      file.print("[]");
      file.close();
    }
  }
  return true;
}

String UserManager::getUsersJson() {
  File file = LittleFS.open(filePath, "r");
  if (!file) return "[]";

  String content = file.readString();
  file.close();
  return content;
}

bool UserManager::addUser(String name, String uid) {
  JsonDocument doc;
  File file = LittleFS.open(filePath, "r");

  if (file) {
    deserializeJson(doc, file);
    file.close();
  }

  JsonArray array = doc.as<JsonArray>();
  if (array.isNull()) {
    array = doc.to<JsonArray>();
  }

  for (JsonObject user : array) {
    if (user["uid"] == uid) return false;
  }

  JsonObject newUser = array.add<JsonObject>();
  newUser["name"] = name;
  newUser["uid"] = uid;

  file = LittleFS.open(filePath, "w");
  if (!file) return false;

  serializeJson(doc, file);
  file.close();
  Serial.printf("![UserManager] %s adicionado.\n", name.c_str());
  return true;
}

bool UserManager::removeUser(String uid) {
  JsonDocument doc;
  File file = LittleFS.open(filePath, "r");

  if (!file) return false;
  deserializeJson(doc, file);
  file.close();

  JsonArray array = doc.as<JsonArray>();
  for (size_t i = 0; i < array.size(); i++) {
    if (array[i]["uid"] == uid) {
      array.remove(i);
      break;
    }
  }

  file = LittleFS.open(filePath, "w");
  if (!file) return false;

  serializeJson(doc, file);
  file.close();
  return true;
}