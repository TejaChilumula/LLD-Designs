#ifndef USER_CONTROLLER_HPP
#define USER_CONTROLLER_HPP

#include <vector>
#include "User.hpp"

class UserController {
private:
    std::vector<User> users;

public:
    void addUser(const User& user) {
        users.push_back(user);
    }

    User* getUser(int userId) {
        for (auto& user : users) {
            if (user.getId() == userId)
                return &user;
        }
        return nullptr;
    }

    const std::vector<User>& getAllUsers() const {
        return users;
    }
};

#endif // USER_CONTROLLER_HPP
