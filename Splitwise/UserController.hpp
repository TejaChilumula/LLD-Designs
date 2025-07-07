#ifndef USER_CONTROLLER_HPP
#define USER_CONTROLLER_HPP

#include <vector>
#include "User.hpp"

class UserController {
private:
    std::vector<User> users;

public:
    // Add a new user
    void addUser(const User& user) {
        users.push_back(user);
    }

    // Retrieve a user by ID (const-safe)
    User* getUser(int userId) const {
        for (auto& user : users) {
            if (user.getId() == userId)
                return const_cast<User*>(&user); // safe if used read-only
        }
        return nullptr;
    }

    // Get all users (read-only access)
    const std::vector<User>& getAllUsers() const {
        return users;
    }
};

#endif // USER_CONTROLLER_HPP
