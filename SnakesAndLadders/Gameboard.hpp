#include<iostream>
#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include<string>
#include<vector>
#include<map>

#include "Player.hpp"
#include "Jump.hpp"
#include "Dice.hpp"

class  Gameboard
{
private:
    int boardSize;
    Dice dice;
    std::vector<Player> players;
    std::map<int, int> jumps;
public:
    int playerCount;
     Gameboard(int bSize, int diceCount, int playerCount) : boardSize(bSize), dice(diceCount), playerCount(playerCount){
        for(int i=0;i<playerCount;i++){
            std::string name;
            std::cout<<"Enter player"<<(i+1)<<"name";
            std::cin>>name;
            players.emplace_back(name);
        }
    }

        // add snake or ladder jump
        void addJump(const Jump& jump){
            jumps[jump.start] = jump.end;
        }

        void startGame(){
            // Initially enqueue all player indices
            std::queue<int> playerQueue;
            for (int i = 0; i < playerCount; ++i) {
                playerQueue.push(i);
            }

            std::cin.ignore();

            while(playerQueue.size() > 1){
                int playerIdx = playerQueue.front();
                playerQueue.pop();
                    
                    Player& player = players[playerIdx];   
                    const std::string& name = player.getName();
                    int cur_pos = player.getPosition();

                    std::cout<<"\n"<<name<<"'s turn Press enter ";
                    std::cin.get();

                    int diceRoll = dice.roll();
                    std::cout<<player.getName()<<"rolled a "<<diceRoll<<std::endl;
                    
                    int nextPos = cur_pos + diceRoll;

                    // checks

                    // if roll exceedboard size
                    if(nextPos > boardSize){
                        std::cout<<"Roll exceeds board size."
                        <<name<<" stays at "<<cur_pos<<std::endl;
                        playerQueue.push(playerIdx);
                    }else {
                        // check for snake or ladder
                        if(jumps.find(nextPos) != jumps.end()){
                            int jumpTo = jumps[nextPos];
                            if(jumpTo > nextPos){
                                     std::cout << "🎉 Ladder from " << nextPos
                                      << " to " << jumpTo << std::endl;
                                } else {
                                    std::cout << "🐍 Snake from " << nextPos
                                            << " to " << jumpTo << std::endl;
                                }
                                nextPos = jumpTo;
                            }
                            // update player pos

                            player.setPosition(nextPos);

                            std::cout << name << " moves to "
                                    << player.getPosition() << std::endl;

                            // Check if player wins
                            if (player.getPosition() == boardSize) {
                                std::cout << "\n🏆 " << name
                                        << " wins the game! Congratulations!" << std::endl;
                                        // If wins wont push again, he got not chances
                            } else playerQueue.push(playerIdx);

                        }
                    }
                    // Last player left
                    if (!playerQueue.empty()) {
                        int lastPlayerIdx = playerQueue.front();
                        std::cout << "\n😞 " << players[lastPlayerIdx].getName()
                                << " is the last player remaining and loses the game." << std::endl;
                    }
                }
        
     };
     #endif
    