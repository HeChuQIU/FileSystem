//
// Created by HeChu on 24-6-28.
//

#include <string>
#include <ctime>

class User {
private:
    std::string username;
    std::string password;
    std::time_t lastLoginTime;

public:
    User(const std::string& username, const std::string& password){
        this->username = username;
        this->password = password;
        this->lastLoginTime = std::time(nullptr);
    }

    std::string Username() const{
        return username;
    }

    bool CheckPassword(const std::string& password) const{
        return this->password == password;
    }

    std::time_t LastLoginTime() const{
        return lastLoginTime;
    }
};
