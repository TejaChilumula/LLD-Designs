#include<string>

class User {
    int id;
    std::string name;
    std::string email;
public:
    User(int id, const std::string& name, const std::string& email = "") : id(id), name(name), email(email) {}

    int getId() const{ return id;}
    const std::string& getName() const { return name;}
    const std::string& getEmail() const { return email;}


};