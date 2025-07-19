#pragma once

#include <vector>
#include <iostream>
#include "GameState.hpp"


using namespace std;

class GameBoard{
    private:
        int size;
        vector<vector<int>> board;
        int totalMoves = 0;
    
        public:
            GameBoard(int n) : size(n), board(n, vector<int>(n,0)){}

            bool isCellEmpty(int row, int col) const {
                return board[row][col] == 0;
            }

            bool makeMove(int row, int col, int playerId){
                if(row<0 || row>= size 
                || col < 0 || col >= size 
                || !isCellEmpty(row,col)) return false;
                
                board[row][col] = playerId;
                totalMoves++;
                return true;
            }

            GameState checkGameState(int lastRow, int lastCol, int playerId) const{
                bool win = true;

                // Check for the row
                for(int j=0;j<size;++j)
                    if(board[lastRow][j] != playerId) win = false;
                if(win) return GameState::WIN;

                win = true;

                for(int i=0;i<size;i++)
                    if (board[i][lastCol] != playerId) win = false;
                if (win) return GameState::WIN;

                if(lastRow == lastCol) // diagonal check
                {   
                    win = true;
                    for(int i=0;i<size;i++){
                        if(board[i][i] != playerId) win = false;
                    if (win) return GameState::WIN;
                    }
                }

                // Check for anti-diagonal

                if(lastRow+lastCol == size-1){
                    win = true;
                    for(int i=0;i<size;++i){
                        if(board[i][size-1-i] != playerId) win = false;
                    if(win) return GameState::WIN;
                    }
                }

                if(totalMoves == size*size)
                    return GameState::DRAW;
                
                
                return GameState::ONGOING;
            }
        
        void printBoard() const {
            cout<<"\nCurrent Board:\n";
            for(int i=0;i<size;++i){
                for(int j=0;j<size;++j){
                    if(board[i][j] == 0)
                        cout<<". ";
                    else  
                        cout<<board[i][j]<<" ";
                }
                cout<<"\n";
            }
            cout<<endl;
        }

        int getSize() const { return size;}

        void reset() {
            for (auto& row : board) {
                std::fill(row.begin(), row.end(), 0);
            }
            totalMoves = 0;
        }
};