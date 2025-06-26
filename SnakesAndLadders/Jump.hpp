#ifndef JUMP_HPP
#define JUMP_HPP

class Jump{

     // simple data holder, so no need getters and setters
    public:
        int start;
        int end;
    Jump(int s, int e) : start(s), end(e) {} 
    // fast , no garbage initialisation and directly initializes and 
    //assigns vals even before constructore call
    /*
        Simpler way - But initialize garbage then assign vals inside constructor
        // if it is of class type Jump j -> then calls its constructor

        Jump(int _start, int _end) // to make clear look _
        {
            this->start = _start;
            this->end = _end;
        }

    */
};
#endif