#ifndef DICE_HPP
#define DICE_HPP

#include <cstdlib>
#include <ctime>

class Dice{
    private:
        int numDice;
    public:
        // constructor
        Dice() {}
        Dice(int n) : numDice(n) {srand(time(0));}

        // above can also written as
        /*
            Dice(int n){
            this->numDice = n;
            }
        */

        // simpler rolling 

        int roll()
        {
            int total = 0;
            for(int i=0;i<numDice;i++){
                total += (rand() % 6 ) + 1;
            }
            return total;
        }


};

#endif