#include<iostream>
#ifndef PLAYER_HPP
#define PLAYER_HPP


class Player{

    private:
        std::string playerName;
        int playerPosition;

    public:
        Player(const std::string &name) : playerName(name), playerPosition(0) {}

        std :: string getName() const {
            return playerName;
        } 

        int getPosition(){
            return playerPosition;
        }

        void setPosition(int pos){
            if(pos >= 0) playerPosition = pos;
        }

        // Only for constructors
        //void resetPosition() : playerPosition(0) {}

};

#endif

