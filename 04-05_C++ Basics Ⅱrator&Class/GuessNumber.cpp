/*
* Author: Junji Wei
* Date: 2018.3.26
* Version: 1.0
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "GuessNumber.h"
using namespace std;

GuessNumber::GuessNumber() {
    times = 0;
    srand((int)time(0));
    number = rand() % 1000 + 1;
}

void GuessNumber::start() {
    welcome();
    while(!guess());
    result();
}

void GuessNumber::welcome() const {
    cout << "I have a number between 1 and 1000" << endl;
    cout << "Can you guess my number?" << endl;
    cout << "Please type your first guess: ";
}

bool GuessNumber::guess() {
    /*
    Read the number in and determine
    |  < -100  | -100 |  -10  | number |  +10  | +100 | > +100   |
    | Too low  | low  | close | right  | close | high | Too high |
    */
    int guess_number;
    cin >> guess_number;
    times++;

    while (cin.fail()) {
        cin.clear();
        cout << "Wrong input, try again: ";
        cin.ignore(1024,'\n');
        cin >> guess_number;
    }

    if (guess_number == number) {
        return true;
    } else if (guess_number > number) {
        // Higher than the number
        if (guess_number > number + 100) {
            cout << "Too high, try again: ";
        } else if (guess_number < number + 10) {
            cout << "High, but very close, try again: ";
        } else {
            cout << "High, try again: ";
        }
    } else {
        // Lower than the number
        if (guess_number < number - 100) {
            cout << "Too low, try again: ";
        } else if (guess_number > number - 10) {
            cout << "Low, but very close, try again: ";
        } else {
            cout << "Low, try again: ";
        }
    }
    return false;
}

void GuessNumber::result() const {
    if (times == 1) {
        cout << "Amazing!!!! ";
    } else if (times < 4) {
        cout << "Perfect!!! ";
    } else if (times < 7) {
        cout << "Excellent!! ";
    } else if (times < 10) {
        cout << "Good! ";
    } else if (times < 12) {
        cout << "Ok. ";
    } else {
        cout << "Badly. ";
    }

    cout << "You guessed the number by " << times << "times." << endl;
}
