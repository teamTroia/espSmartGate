#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <ArduinoJson.h>
#include <LittleFS.h>
#include <vector>

struct User {
    String name;
    String uid;
};

class UserManager {
public:
    UserManager();
    bool begin();
    bool addUser(String name, String uid);
    bool removeUser(String uid);
    String getUsersJson();

private:
    const char* filePath = "/users.json";
};

#endif