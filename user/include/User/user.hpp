//
// Created by HeChu on 24-6-28.
//

#ifndef FILESYSTEM_USER_HPP
#define FILESYSTEM_USER_HPP

#include <string>
#include <ctime>

class User {
private:
    std::string username;
    std::string password;
    std::time_t lastLoginTime;

public:
    User(const std::string& username, const std::string& password);

    std::string Username() const;
    bool CheckPassword(const std::string& password) const;
    std::time_t LastLoginTime() const;
};

#endif //FILESYSTEM_USER_HPP
