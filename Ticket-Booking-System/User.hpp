#pragma once
#include<string>

using namespace std;
class User{
private:
    int userId;
    string name;

public:
    User(int _userid, const string& _name ) : userId(_userid), name(_name) {};
    
    int getId() const { return userId;}
    string getName() const {return name;}
};