/*
* Author: Junji Wei
* Date: 2018.3.26
* Version: 1.0
*/

#include <iostream>
#include "GuessNumber.h"
using namespace std;

bool tryAgain() {
    cin.clear();
    cin.ignore(1024,'\n');
    cout << "Would you like to play again (y or n)? ";
    char ans;
    ans = cin.get();

    while (cin.fail() && ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N') {
        cin.clear();
        cout << "Wrong input, try again: ";
        cin.ignore(1024,'\n');
        ans = cin.get();
    }

    return ans == 'y' || ans == 'Y';
}

int main() {
    do {
        GuessNumber game = GuessNumber();
        game.start();
    } while (tryAgain());
    cout << "Goodbye" << endl;
    return 0;
}
