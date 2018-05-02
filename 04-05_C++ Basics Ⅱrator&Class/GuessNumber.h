/*
* Author: Junji Wei
* Date: 2018.3.26
* Version: 1.0
*/

#ifndef GUESS_NUMBER_H
#define GUESS_NUMBER_H

class GuessNumber {
    private:
        int number;
        int times;
        void welcome() const;
        bool guess();
        void result() const;
    
    public:
        GuessNumber();
        void start();
};

#endif // !GUESS_NUMBER_H
