#ifndef GROUP_CONTROLLER_HPP
#define GROUP_CONTROLLER_HPP

#include <vector>
#include <string>
#include <iostream>
#include "Group.hpp"

class GroupController {
private:
    std::vector<Group> groupList;

public:
    // Create and return reference to the new group
    Group& createNewGroup(const std::string& groupId, const std::string& groupName, const User& createdByUser) {
        groupList.emplace_back(groupId, groupName, std::vector<User>{createdByUser});
        return groupList.back();
    }

    // Get pointer to group by ID (nullptr if not found)
    Group* getGroup(const std::string& groupId) {
        for (auto& group : groupList) {
            if (group.getId() == groupId) return &group;
        }
        std::cout << "No such group exists!" << std::endl;
        return nullptr;
    }

    // Get all groups
    const std::vector<Group>& getAllGroups() const {
        return groupList;
    }
};

#endif // GROUP_CONTROLLER_HPP
